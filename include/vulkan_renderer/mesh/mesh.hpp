#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "../renderer_utils.hpp"

class Mesh {
    public:
        virtual std::vector<Vertex> get_vertices() = 0;
        virtual std::vector<uint32_t> get_indices() = 0;
};

#endif // MESH_HPP
