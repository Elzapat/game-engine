#include "../include/vulkan_renderer.hpp"

bool QueueFamilyIndices::is_complete() {
    return this->graphics_family.has_value() && this->present_family.has_value();
}

void VulkanRenderer::run() {}
