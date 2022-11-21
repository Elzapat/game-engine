#ifndef PLANE_HPP
#define PLANE_HPP

#include "primitive.hpp"
#include "math/vector3.hpp"

class Plane : Primitive
{
private:
    float off_set;
    math::Vector3 normal;

public:
    Plane(/* args */);
    ~Plane();
};

#endif