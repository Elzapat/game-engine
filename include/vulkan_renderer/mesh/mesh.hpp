#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "../renderer_utils.hpp"

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
};

#endif // MESH_HPP
