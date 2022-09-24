#include "../../include/vulkan_renderer/renderer_utils.hpp"

bool QueueFamilyIndices::is_complete() {
    return this->graphics_family.has_value() && this->present_family.has_value();
}

VkVertexInputBindingDescription Vertex::get_binding_description() {
    VkVertexInputBindingDescription binding_description {};
    binding_description.binding = 0;
    binding_description.stride = sizeof(Vertex);
    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return binding_description;
}

std::array<VkVertexInputAttributeDescription, 2> Vertex::get_attribute_description() {
    std::array<VkVertexInputAttributeDescription, 2> attribute_description {};

    attribute_description[0].binding = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_description[0].offset = offsetof(Vertex, pos);

    attribute_description[1].binding = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_description[1].offset = offsetof(Vertex, color);

    return attribute_description;
}

std::vector<char> read_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}
