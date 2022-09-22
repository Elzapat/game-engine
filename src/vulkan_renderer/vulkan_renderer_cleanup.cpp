#include "../../include/vulkan_renderer/vulkan_renderer.hpp"

void VulkanRenderer::cleanup() {
    this->clean_swapchain();

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

void VulkanRenderer::clean_swapchain() {
    vkDestroySwapchainKHR(this->device, this->swapchain, nullptr);

    for (auto image_view : swapchain_image_views) {
        vkDestroyImageView(this->device, image_view, nullptr);
    }

    for (auto framebuffer : this->swapchain_framebuffers) {
        vkDestroyFramebuffer(this->device, framebuffer, nullptr);
    }
}
