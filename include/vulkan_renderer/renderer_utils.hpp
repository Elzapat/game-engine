#ifndef RENDERER_UTILS_HPP
#define RENDERER_UTILS_HPP

// clang-format off

#include "../../include/math/vector3D.hpp"

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <optional>
#include <array>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <memory>

std::vector<char> read_file(const std::string& filename);
void copy_buffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
bool has_stencil_component(VkFormat format);
void* aligned_malloc(size_t size, size_t alignment);
void aligned_free(void* data);

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

struct Vertex {
    /* math::Vector3D pos; */
    /* math::Vector3D color; */
    math::Vector3D pos;
    math::Vector3D color;

    static VkVertexInputBindingDescription get_binding_description();
    static std::array<VkVertexInputAttributeDescription, 2> get_attribute_description();
};

#include <glm/glm.hpp>
/*
struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};
*/

struct UniformBuffers {
    VkBuffer view;
    VkDeviceMemory view_buffer_memory;

    VkBuffer dynamic;
    VkDeviceMemory dynamic_buffer_memory;
};

struct UboVS {
    glm::mat4 view;
    glm::mat4 projection;
};

struct UboData {
    glm::mat4 model;
    glm::vec3 color;
};

struct UboDataDynamic {
    UboData* data;
};

struct InstanceData {
    math::Vector3D position;
};

#endif // RENDERER_UTILS_HPP
