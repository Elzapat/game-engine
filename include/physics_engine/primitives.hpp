#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <memory>

#include "math/vector3.hpp"
#include "physics_engine/rigid_body.hpp"

class Primitive {
    public:
        virtual ~Primitive() = default;
        std::shared_ptr<RigidBody> rigid_body;
        math::Matrix4 offset;

        math::Matrix4 get_transform() const;
        math::Vector3 get_axis(int i) const;
};

class Box: public Primitive {
    public:
        math::Vector3 half_size;
};

class Sphere: public Primitive {
    public:
        float radius;
};

class Plane: public Primitive {
    public:
        float offset;
        math::Vector3 normal;
};

#endif  // PRIMITIVES_HPP
