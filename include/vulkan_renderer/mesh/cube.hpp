#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include "mesh.hpp"
#include "../renderer_utils.hpp"

class Cube : public Mesh {
    public:
        std::vector<Vertex> get_vertices() override;
        std::vector<uint32_t> get_indices() override;
};

#endif // CUBE_HPP
