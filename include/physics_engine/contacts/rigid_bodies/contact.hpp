#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <memory>

#include "math/matrix3.hpp"
#include "math/quaternion.hpp"
#include "math/vector3.hpp"
#include "physics_engine/rigid_body.hpp"

class ContactResolver;
class CollisionDetector;

class Contact {
    public:
        Contact(
            std::shared_ptr<RigidBody> _first,
            std::shared_ptr<RigidBody> _second,
            float _friction,
            float _restitution
        );

    private:
        friend CollisionDetector;
        friend ContactResolver;

        std::shared_ptr<RigidBody> first;
        std::shared_ptr<RigidBody> second;

        float friction;
        float restitution;

        math::Vector3 contact_point;
        math::Vector3 contact_normal;
        float penetration;

        math::Vector3
        calculate_local_velocity(std::shared_ptr<RigidBody> body, math::Vector3& rel_contact_pos);
        void calculate_desired_delta_velocity();
        void calculate_contact_basis();
        math::Vector3 calculate_frictionless_impulse(std::array<math::Matrix3, 2> inverse_inertia_tensors);

    protected:
        math::Matrix3 contact_to_world;

        std::array<math::Vector3, 2> relative_contact_pos;

        math::Vector3 contact_velocity;
        float desired_delta_velocity;

        void swap_bodies();
        void calculate_internals();
        void resolve_interpenetration(
            std::array<math::Vector3, 2>& linear_change,
            std::array<math::Vector3, 2>& angular_change,
            float penetration
        );
        void resolve_velocity(
            std::array<math::Vector3, 2>& velocity_change,
            std::array<math::Vector3, 2>& rotation_change
        );
        std::shared_ptr<RigidBody> get_body(int index);
};
#endif  // CONTACT_HPP
