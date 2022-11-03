#include "vulkan_renderer/vulkan_renderer.hpp"

VulkanRenderer::~VulkanRenderer() {
    /* this->cleanup(); */
    vkDeviceWaitIdle(this->device);
}

void VulkanRenderer::cleanup() {
    this->cleanup_swapchain();

    aligned_free(this->ubo_data_dynamic);

    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    vkDestroyImageView(this->device, this->depth_image_view, nullptr);
    vkDestroyImage(this->device, this->depth_image, nullptr);
    vkFreeMemory(this->device, this->depth_image_memory, nullptr);

    vkDestroyBuffer(this->device, this->uniform_buffers.view, nullptr);
    vkFreeMemory(this->device, this->uniform_buffers.view_buffer_memory, nullptr);
    vkDestroyBuffer(this->device, this->uniform_buffers.dynamic, nullptr);
    vkFreeMemory(this->device, this->uniform_buffers.dynamic_buffer_memory, nullptr);

    vkDestroyDescriptorPool(this->device, this->descriptor_pool, nullptr);
    vkDestroyDescriptorSetLayout(this->device, this->descriptor_set_layout, nullptr);

    vkDestroyBuffer(this->device, this->index_buffer, nullptr);
    vkFreeMemory(this->device, this->index_buffer_memory, nullptr);

    vkDestroyBuffer(this->device, this->vertex_buffer, nullptr);
    vkFreeMemory(this->device, this->vertex_buffer_memory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->device, this->image_available_semaphores[i], nullptr);
        vkDestroySemaphore(this->device, this->render_finished_semaphores[i], nullptr);
        vkDestroyFence(this->device, this->in_flight_fences[i], nullptr);
    }

    vkDestroyCommandPool(this->device, this->command_pool, nullptr);

    vkDestroyPipeline(this->device, this->graphics_pipeline, nullptr);
    vkDestroyRenderPass(this->device, this->render_pass, nullptr);
    vkDestroyPipelineLayout(this->device, this->pipeline_layout, nullptr);

    if (enable_validation_layers) {
        destroy_debug_utils_messenger_EXT(this->instance, this->debug_messenger, nullptr);
    }

    vkDestroyDevice(this->device, nullptr);
    vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
    vkDestroyInstance(this->instance, nullptr);

    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void VulkanRenderer::cleanup_swapchain() {
    vkDestroyImageView(this->device, this->depth_image_view, nullptr);
    vkDestroyImage(this->device, this->depth_image, nullptr);
    vkFreeMemory(this->device, this->depth_image_memory, nullptr);

    vkDestroySwapchainKHR(this->device, this->swapchain, nullptr);

    for (auto image_view : swapchain_image_views) {
        vkDestroyImageView(this->device, image_view, nullptr);
    }

    for (auto framebuffer : this->swapchain_framebuffers) {
        vkDestroyFramebuffer(this->device, framebuffer, nullptr);
    }
}
