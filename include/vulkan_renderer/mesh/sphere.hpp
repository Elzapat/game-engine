#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include <cmath>

#include "mesh.hpp"
#include "../renderer_utils.hpp"

class Sphere : public Mesh {
    public:
        Sphere(float radius = 1.0f, int slices = 36, int stacks = 18);

        float radius;
        int sectors;
        int stacks;
};

#endif // SPHERE_HPP
