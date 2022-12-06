#ifndef PLANE_HPP
#define PLANE_HPP

#include "math/vector3.hpp"
#include "primitive.hpp"

class Plane: public Primitive {
    public:
        float offset;
        math::Vector3 normal;
};

#endif
