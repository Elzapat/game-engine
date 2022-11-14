#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <vulkan/vulkan.h>

#include "renderer_utils.hpp"

class Mesh {
    public:
        enum class MeshType {
            Sphere,
            Cube,
            Custom,
        };

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        MeshType type;
        math::Vector3 scale = math::Vector3(1.0f, 1.0f, 1.0f);
        math::Vector3 color = math::Vector3(1.0f, 1.0f, 1.0f);

        VkBuffer vertex_buffer;
        VkDeviceMemory vertex_buffer_memory;

        VkBuffer index_buffer;
        VkDeviceMemory index_buffer_memory;

        Mesh(MeshType type, std::vector<Vertex> vertices, std::vector<uint32_t> indices);
        ~Mesh();

        static Mesh sphere(float radius, int sectors, int stacks);
        static Mesh cube();
};

#endif // MESH_HPP
