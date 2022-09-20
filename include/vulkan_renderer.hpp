#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

// clang-format off

#include <vulkan/vulkan.h>
#include "glfw/include/GLFW/glfw3.h"

#include <vector>
#include <set>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool is_complete();
};

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

class VulkanRenderer {
    public:
        void run();

    private:
        GLFWwindow* window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debug_messenger;

        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkSurfaceKHR surface;
        VkDevice device;

        VkQueue graphics_queue;
        VkQueue present_queue;

        VkSwapchainKHR swapchain;
        std::vector<VkImage> swapchain_images;
        std::vector<VkImageView> swapchain_image_views;
        VkFormat swapchain_image_format;
        VkExtent2D swapchain_extent;

        VkRenderPass render_pass;
        VkPipelineLayout pipeline_layout;
        VkPipeline graphics_pipeline;

        std::vector<VkFramebuffer> swapchain_framebuffers;
        VkCommandPool command_pool;
        std::vector<VkCommandBuffer> command_buffers;

        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;

        bool framebuffer_resized = false;
        uint32_t current_frame = 0;

        // Initialization
        void init_window();
        void init_vulkan();

        // Creation of needed Vulkan objects
        void create_instance();
        void create_surface();
        void create_logical_device();
        void create_swapchain();
        void create_image_views();
        void create_render_pass();
        void craete_graphics_pipeline();
        void create_framebuffer();
        void create_command_pool();
        void create_command_buffers();
        void create_sync_objects();

        // Update what's on the screen
        void record_command_buffers();
        void draw_frame();
        void framebuffer_resized_callback(GLFWwindow* window, int width, int height);

        // Helpers to create swapchain
        VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats);
        VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& available_present_modes);
        VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);

        // Helper functions
        // Picks a physical device, such as a GPU
        void pick_physical_device();
        // Checks if the chosen device is suitable, meaning if it has the required features
        bool is_device_suitable();
        // Checks if the chosen device support the correct extensions
        bool check_device_extension_support(VkPhysicalDevice device);
        // Checks if the library supports validation layers
        bool check_validation_layer_support();
        VkShaderModule create_shader_module();
        // Finds the indices of the different queues we need (graphics and present queue) 
        QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
        SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice device);
        std::vector<const char*> get_required_extensions();

        // Cleanup functions
        void cleanup();
        void clean_swapchain();

        // Debug functions
        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
            VkDebugUtilsMessageTypeFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
            void* p_user_data
        );
        void setup_debug_messenger();
};

#endif  // VULKAN_RENDERER_HPP
