#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../../math/matrix4.hpp"
#include "../rigid_body.hpp"

class Primitive
{
private:
    math::Matrix4 off_set;
    RigidBody body;

public:
    Primitive(/* args */);
    ~Primitive();
};

#endif