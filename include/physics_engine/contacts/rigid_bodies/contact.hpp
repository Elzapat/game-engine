#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <memory>

#include "math/vector3.hpp"
#include "physics_engine/rigid_body.hpp"

class Contact {
    public:
        std::shared_ptr<RigidBody> first;
        std::shared_ptr<RigidBody> second;

        float friction;
        float restitution;

        math::Vector3 contact_point;
        math::Vector3 contact_normal;
        float penetration;

        Contact(
            std::shared_ptr<RigidBody> _first,
            std::shared_ptr<RigidBody> _second,
            float _friction,
            float _restitution
        );
};

#endif  // CONTACT_HPP
