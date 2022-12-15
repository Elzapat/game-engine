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

        math::Matrix3 contact_to_world;

        Contact(
            std::shared_ptr<RigidBody> _first,
            std::shared_ptr<RigidBody> _second,
            float _friction,
            float _restitution
        );

    private:
        math::Vector3 first_relative_contact_pos;
        math::Vector3 second_relative_contact_pos;

        math::Vector3 contact_velocity;
        float desired_delta_velocity;

        void calculate_internals();
        math::Vector3 calculate_local_velocity(std::shared_ptr<RigidBody> body, math::Vector3& rel_contact_pos);
        void calculate_desired_delta_velocity();
        void calculate_contact_basis();
        math::Vector3 calculate_frictionless_impulse(math::Matrix3& inverse_inertia_tensor);
};
#endif  // CONTACT_HPP
