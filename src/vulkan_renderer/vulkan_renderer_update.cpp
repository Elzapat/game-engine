#include "../../include/vulkan_renderer/vulkan_renderer.hpp"

void VulkanRenderer::draw() {
    this->draw_frame();
}

void VulkanRenderer::draw_frame() {
    uint32_t image_index;
    VkResult result = vkAcquireNextImageKHR(
        this->device,
        this->swapchain,
        UINT64_MAX,
        this->image_available_semaphores[this->current_frame],
        VK_NULL_HANDLE,
        &image_index
    );

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreate_swapchain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to acquire swap chain image");
    }

    vkResetFences(this->device, 1, &this->in_flight_fences[this->current_frame]);

    vkResetCommandBuffer(this->command_buffers[this->current_frame], 0);
    this->record_command_buffer(this->command_buffers[this->current_frame], image_index);
    this->update_uniform_buffer(this->current_frame);

    VkSubmitInfo submit_info {};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = {this->image_available_semaphores[this->current_frame]};
    VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = wait_semaphores;
    submit_info.pWaitDstStageMask = wait_stages;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &this->command_buffers[this->current_frame];

    VkSemaphore signal_semaphores[] = {this->render_finished_semaphores[this->current_frame]};
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = signal_semaphores;

    result = vkQueueSubmit(
        this->graphics_queue,
        1,
        &submit_info,
        this->in_flight_fences[this->current_frame]
    );
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer");
    }

    vkWaitForFences(
        this->device,
        1,
        &this->in_flight_fences[this->current_frame],
        VK_TRUE,
        UINT64_MAX
    );

    VkPresentInfoKHR present_info {};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapchains[] = {this->swapchain};
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapchains;
    present_info.pImageIndices = &image_index;

    result = vkQueuePresentKHR(this->present_queue, &present_info);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
        || this->framebuffer_resized) {
        this->framebuffer_resized = false;
        this->recreate_swapchain();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swap chain image");
    }

    this->current_frame = (this->current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderer::record_command_buffer(VkCommandBuffer command_buffer, uint32_t image_index) {
    VkCommandBufferBeginInfo begin_info {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = 0;
    begin_info.pInheritanceInfo = nullptr;

    VkResult result = vkBeginCommandBuffer(command_buffer, &begin_info);
    check_vk_result(result, "Failed to begin recording command buffer");

    VkRenderPassBeginInfo render_pass_info {};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = this->render_pass;
    render_pass_info.framebuffer = swapchain_framebuffers[image_index];
    render_pass_info.renderArea.offset = {0, 0};
    render_pass_info.renderArea.extent = this->swapchain_extent;

    std::array<VkClearValue, 2> clear_values {};
    clear_values[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    clear_values[1].depthStencil = {1.0f, 0};

    render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
    render_pass_info.pClearValues = clear_values.data();

    vkCmdBeginRenderPass(command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->graphics_pipeline);

    VkViewport viewport {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain_extent.width);
    viewport.height = static_cast<float>(swapchain_extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(command_buffer, 0, 1, &viewport);

    VkRect2D scissor {};
    scissor.offset = {0, 0};
    scissor.extent = this->swapchain_extent;
    vkCmdSetScissor(command_buffer, 0, 1, &scissor);

    VkBuffer vertex_buffers[] = {this->vertex_buffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(command_buffer, 0, 1, vertex_buffers, offsets);

    vkCmdBindIndexBuffer(command_buffer, this->index_buffer, 0, VK_INDEX_TYPE_UINT16);

    for (uint32_t j = 0; j < MAX_OBJECT_INSTANCES; j++) {
        uint32_t dynamic_offset = j * static_cast<uint32_t>(this->dynamic_alignment);

        vkCmdBindDescriptorSets(
            command_buffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            this->pipeline_layout,
            0,
            1,
            &this->descriptor_set,
            1,
            &dynamic_offset
        );

        vkCmdDrawIndexed(command_buffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
    }

    Particle temp = Particle();
    ui.draw(1, temp, this->camera.rotation);
    ui.render(command_buffer);

    vkCmdEndRenderPass(command_buffer);

    result = vkEndCommandBuffer(command_buffer);
    check_vk_result(result, "Failed to record command buffer");
}

void VulkanRenderer::update_uniform_buffer(uint32_t current_image) {
    float x_i = 0.0f, y_i = 0.0f, z_i = 0.0f;

    for (int i = 0; i < MAX_OBJECT_INSTANCES; i++) {
        uint32_t index = i * this->dynamic_alignment;
        UboData* ubo_data = (UboData*)((uint64_t)this->ubo_data_dynamic + index);

        const float offset = 2.0f;

        if (i % 4) {
            ubo_data->color = glm::vec3(1.0f, 0.0f, 0.0f);
            ubo_data->model = glm::translate(glm::mat4(1.0), glm::vec3(x_i++ * offset, 0.0f, 0.0f));
        } else if (i % 3) {
            ubo_data->color = glm::vec3(0.0f, 1.0f, 0.0f);
            ubo_data->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, y_i++ * offset, 0.0f));
        } else {
            ubo_data->color = glm::vec3(0.0f, 0.0f, 1.0f);
            ubo_data->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, z_i++ * offset));
        }

        // ubo_data->color = this->cubes_colors[i];
        // ubo_data->model = glm::translate(glm::mat4(1.0), glm::vec3(i * offset, 0.0f, 0.0f));
    }

    void* data;
    vkMapMemory(
        this->device,
        this->uniform_buffers.dynamic_buffer_memory,
        0,
        MAX_OBJECT_INSTANCES * dynamic_alignment,
        0,
        &data
    );
    memcpy(data, this->ubo_data_dynamic, MAX_OBJECT_INSTANCES * dynamic_alignment);
    VkMappedMemoryRange memory_range = {};
    memory_range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memory_range.memory = this->uniform_buffers.dynamic_buffer_memory;
    memory_range.offset = 0;
    memory_range.size = MAX_OBJECT_INSTANCES * dynamic_alignment;

    vkFlushMappedMemoryRanges(this->device, 1, &memory_range);

    vkUnmapMemory(this->device, this->uniform_buffers.dynamic_buffer_memory);

    UboVS ubo_vs {};
    ubo_vs.projection = glm::perspective(
        glm::radians(45.0f),
        this->swapchain_extent.width / (float)this->swapchain_extent.height,
        0.1f,
        100.0f
    );
    ubo_vs.projection[1][1] *= -1.0f;
    ubo_vs.view = camera.view;
    /*
    glm::lookAt(
        glm::vec3(this->ui.eye_x, this->ui.eye_y, this->ui.eye_z),
        glm::vec3(this->ui.look_at_x, this->ui.look_at_y, this->ui.look_at_z),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    */

    vkMapMemory(
        this->device,
        this->uniform_buffers.view_buffer_memory,
        0,
        sizeof(ubo_vs),
        0,
        &data
    );
    memcpy(data, &ubo_vs, sizeof(ubo_vs));
    vkUnmapMemory(this->device, this->uniform_buffers.view_buffer_memory);
}

void VulkanRenderer::update_camera(float dt) {
    this->camera.keys.forwards = glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS;
    this->camera.keys.backwards = glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS;
    this->camera.keys.right = glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS;
    this->camera.keys.left = glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS;
    this->camera.keys.up = glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS;
    this->camera.keys.down = glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS;

    camera.update(dt);
}

void VulkanRenderer::framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    auto renderer = reinterpret_cast<VulkanRenderer*>(glfwGetWindowUserPointer(window));
    renderer->framebuffer_resized = true;
}

void VulkanRenderer::mouse_callback(GLFWwindow* window, double x_pos, double z_pos) {
    auto renderer = reinterpret_cast<VulkanRenderer*>(glfwGetWindowUserPointer(window));

    static int width = 0.0f, height = 0.0f;
    if (width == 0.0f && height == 0.0f) {
        glfwGetFramebufferSize(window, &width, &height);
    }

    static float last_x = static_cast<float>(width) / 2.0f;
    static float last_z = static_cast<float>(height) / 2.0f;

    static bool first_mouse = true;
    if (first_mouse) {
        last_x = x_pos;
        last_z = z_pos;
        first_mouse = false;
    }

    float x_offset = (x_pos - last_x) * renderer->camera.sensitivity;
    float z_offset = (z_pos - last_z) * renderer->camera.sensitivity;

    last_x = x_pos;
    last_z = z_pos;

    renderer->camera.rotation.set_x(renderer->camera.rotation.get_x() + x_offset);
    renderer->camera.rotation.set_z(
        std::clamp(renderer->camera.rotation.get_z() + z_offset, -89.0f, 89.0f)
    );
}