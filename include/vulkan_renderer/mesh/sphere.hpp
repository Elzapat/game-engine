#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include <cmath>

#include "mesh.hpp"
#include "../renderer_utils.hpp"

static const float SPHERE_RADIUS = 1.0f;
static const int SLICES = 10;
static const int STACKS = 10;

class Sphere : public Mesh {
    public:
        std::vector<Vertex> get_vertices() override;
        std::vector<uint32_t> get_indices() override;
};

#endif // SPHERE_HPP
