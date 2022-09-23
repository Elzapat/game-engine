#include "../../include/vulkan_renderer/vulkan_renderer.hpp"

void VulkanRenderer::setup_debug_messenger() {
    if (!enable_validation_layers) {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info.pfnUserCallback = debug_callback;
    create_info.pUserData = nullptr;

    VkResult result = create_debug_utils_messenger_EXT(
        this->instance,
        &create_info,
        nullptr,
        &this->debug_messenger
    );
    check_vk_result(result, "Failed to setup debug messenger");
}

VkResult create_debug_utils_messenger_EXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* p_create_info,
    const VkAllocationCallbacks* p_allocator,
    VkDebugUtilsMessengerEXT* p_debug_messenger
) {
    // clang-format off
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    // clang-format on

    if (func != nullptr) {
        return func(instance, p_create_info, p_allocator, p_debug_messenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void destroy_debug_utils_messenger_EXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debug_messenger,
    const VkAllocationCallbacks* p_allocator
) {
    // clang-format off
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    // clang-format on

    if (func != nullptr) {
        func(instance, debug_messenger, p_allocator);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
    void* p_user_data
) {
    std::cerr << "validation layer: " << p_callback_data->pMessage << std::endl;

    return VK_FALSE;
}

void check_vk_result(VkResult result, std::string message) {
    if (result != VK_SUCCESS) {
        throw std::runtime_error(message);
    }
}
