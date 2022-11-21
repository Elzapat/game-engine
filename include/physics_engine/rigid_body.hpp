#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

#include "math/matrix4.hpp"
#include "math/matrix3.hpp"
#include "math/quaternion.hpp"
#include "math/vector3.hpp"

#include "time.hpp"

/* 
 * Class representing a rigid body wich can be rotated and translated
 */
class RigidBody {
    private:
        float inv_mass = 0.0f;

        math::Vector3 velocity = math::Vector3();
        float linear_damping = 0.99f;

        math::Vector3 rotation = math::Vector3();
        float angular_damping = 0.99f;

        math::Vector3 linear_acceleration = math::Vector3();
        math::Vector3 angular_acceleration = math::Vector3();

        math::Vector3 position = math::Vector3();
        math::Quaternion orientation = math::Quaternion();
        math::Matrix4 transform = math::Matrix4();

        math::Matrix3 inv_inertia_tensor = math::Matrix3();
        math::Matrix3 inv_inertia_tensor_world = math::Matrix3();
        
        math::Vector3 forces = math::Vector3();
        math::Vector3 torques = math::Vector3();

        void compute_derived_data();
        math::Matrix3 transform_inertia_tensor(
            const math::Quaternion& orientation,
            const math::Matrix3& inv_inertia_tensor,
            const math::Matrix4& transform
        );

    public:
        RigidBody();
        ~RigidBody();

        void add_force(const math::Vector3& force);
        void add_force_at_world_point(const math::Vector3& force, math::Vector3 point);
        void add_force_at_local_point(const math::Vector3& force, math::Vector3 point);
        void add_torque(const math::Vector3& torque);
        void apply_impulse(const math::Vector3& impulse);

        math::Vector3 get_point_in_world_space(const math::Vector3& point);
        void set_position(const math::Vector3 pos);
        void set_velocity(const math::Vector3 vel);
        void set_linear_damping(const float linear_damping);
        void set_angular_damping(const float angular_damping);
        void set_rotation(const math::Vector3 rot);
        void set_orientation(const math::Quaternion orientation);
        void set_transform(const math::Matrix4 transform);
        void set_inv_mass(const float inv_mass);
        void set_mass(const float mass);
        void set_inertia_tensor(const math::Matrix3& inertia_tensor);

        math::Vector3 get_position() const;
        math::Vector3 get_velocity() const;
        float get_linear_damping() const;
        float get_angular_damping() const;
        math::Vector3 get_rotation() const;
        math::Quaternion get_orientation() const;
        math::Matrix4 get_transform() const;
        float get_inv_mass() const;
        float get_mass() const;
        bool has_infinite_mass() const;
        math::Matrix3 get_inertia_tensor() const;

        void integrate();
};

#endif  // RIGID_BODY_HPP
