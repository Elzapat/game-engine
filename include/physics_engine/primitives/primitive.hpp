#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <memory>

#include "../../math/matrix4.hpp"
#include "../rigid_body.hpp"

class Primitive {
    public:
        std::shared_ptr<RigidBody> rigid_body;
        math::Matrix4 offset;
};

#endif
