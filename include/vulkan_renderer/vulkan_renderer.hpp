#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

// clang-format off

#include <vulkan/vulkan.h>
#include "../../libs/glfw/include/GLFW/glfw3.h"
#include "../../libs/imgui/backends/imgui_impl_vulkan.h"
#include "../../libs/imgui/backends/imgui_impl_glfw.h"

#include <limits>
#include <algorithm>
#include <vector>
#include <set>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ui.hpp"
#include "renderer_utils.hpp"

static const int WIDTH = 800;
static const int HEIGHT = 600;
static const int MAX_FRAMES_IN_FLIGHT = 2;

static const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
static const std::vector<const char*> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifdef NDEBUG
static const bool enable_validation_layers = false;
#else
static const bool enable_validation_layers = true;
#endif

static std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, -0.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
};

static const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0, 0};

void check_vk_result(VkResult result, std::string message);
VkResult create_debug_utils_messenger_EXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* p_create_info,
    const VkAllocationCallbacks* p_allocator,
    VkDebugUtilsMessengerEXT* p_debug_messenger
);
void destroy_debug_utils_messenger_EXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debug_messenger,
    const VkAllocationCallbacks* p_allocator
);

class VulkanRenderer {
    public:
        void run();

    private:
        Ui ui;
        PhysicWorld physic_world;

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
        VkDescriptorSetLayout descriptor_set_layout;
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

        VkBuffer vertex_buffer;
        VkDeviceMemory vertex_buffer_memory;

        VkBuffer index_buffer;
        VkDeviceMemory index_buffer_memory;

        std::vector<VkBuffer> uniform_buffers;
        std::vector<VkDeviceMemory> uniform_buffers_memory;

        VkDescriptorPool descriptor_pool;
        std::vector<VkDescriptorSet> descriptor_sets;

        // --- Initialization
        void init_window();
        void init_vulkan();
        void init_imgui();

        // --- Creation of needed Vulkan objects
        void create_instance();
        void create_surface();
        void create_logical_device();
        void create_swapchain();
        void create_image_views();
        void create_render_pass();
        void create_descriptor_set_layout();
        void create_graphics_pipeline();
        void create_framebuffers();
        void create_command_pool();
        void create_vertex_buffer();
        void create_index_buffer();
        void create_uniform_buffers();
        void create_command_buffers();
        void create_sync_objects();
        void create_descriptor_pool();
        void create_descriptor_sets();

        // --- Update what's on the screen
        void main_loop();
        void record_command_buffer(VkCommandBuffer command_buffer, uint32_t image_index);
        void draw_frame();
        void update_uniform_buffer(uint32_t current_image);
        static void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

        // --- Helpers to create swapchain
        VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats);
        VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& available_present_modes);
        VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);

        // --- Helper functions
        // Recreates the swapchain when it becomes outdated, in the case of a window resize for example
        void recreate_swapchain();
        // Picks a physical device, such as a GPU
        void pick_physical_device();
        // Checks if the chosen device is suitable, meaning if it has the required features
        bool is_device_suitable(VkPhysicalDevice device);
        // Checks if the chosen device support the correct extensions
        bool check_device_extension_support(VkPhysicalDevice device);
        // Checks if the library supports validation layers
        bool check_validation_layer_support();
        VkShaderModule create_shader_module(const std::vector<char>& code);
        // Finds the indices of the different queues we need (graphics and present queue) 
        QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
        SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice device);
        std::vector<const char*> get_required_extensions();
        void copy_buffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
        void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory);
        uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);
        VkCommandBuffer begin_single_time_commands();
        void end_single_time_commands(VkCommandBuffer command_buffer);

        // --- Cleanup functions
        void cleanup();
        void clean_swapchain();

        // --- Debug functions
        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
            VkDebugUtilsMessageTypeFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
            void* p_user_data
        );
        void setup_debug_messenger();
};

#endif  // VULKAN_RENDERER_HPP
