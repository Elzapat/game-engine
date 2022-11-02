#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "renderer_utils.hpp"

class Mesh {
    enum class MeshType {
        Sphere,
        Cube,
        Custom,
    };

    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        MeshType type;

        VkBuffer vertex_buffer;
        VkBuffer index_buffer;

        Mesh(MeshType type, std::vector<Vertex> vertices, std::vector<uint32_t> indices);

        static Mesh sphere(float radius, int sectors, int stacks);
        static Mesh cube();

};

#endif // MESH_HPP
