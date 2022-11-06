#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

#include "math/matrix4.hpp"
#include "math/quaternion.hpp"
#include "math/vector3.hpp"

#include "time.hpp"

/* 
 * Class representing a rigid body wich can be rotated and translated
 */
class RigidBody {
    private:
        float inv_mass = 0.0f;

        math::Vector3 linear_velocity;
        float linear_damping = 0.99f;

        math::Vector3 angular_velocity;
        float angular_damping = 0.99f;

        math::Vector3 linear_acceleration;
        math::Vector3 angular_acceleration;

        math::Vector3 position;
        math::Quaternion orientation;
        math::Vector3 rotation;
        math::Matrix4 transform;
        
        math::Vector3 forces;
        math::Vector3 torques;

        void compute_derived_data();

    public:
        RigidBody();
        ~RigidBody();

        void add_force(const math::Vector3& force);
        void add_force_at_world_point(const math::Vector3& force, math::Vector3 point);
        void add_force_at_local_point(const math::Vector3& force, math::Vector3 point);
        void add_torque(const math::Vector3& torque);
        void apply_impulse(const math::Vector3& impulse);

        math::Vector3 get_point_in_world_space(const math::Vector3& point);

        void set_posisition(const math::Vector3 pos);
        void set_linear_velocity(const math::Vector3 vel);
        void set_linear_damping(const float linear_damping);
        void set_angular_velocity(const math::Vector3 vel);
        void set_angular_damping(const float angular_damping);
        void set_rotation(const math::Vector3 rot);
        void set_orientation(const math::Quaternion orientation);
        void set_transform(const math::Matrix4 transform);
        void set_inv_mass(const float inv_mass);
        void set_mass(const float mass);

        math::Vector3 get_position() const;
        math::Vector3 get_linear_velocity() const;
        float get_linear_damping() const;
        math::Vector3 get_angular_velocity() const;
        float get_angular_damping() const;
        math::Vector3 get_rotation() const;
        math::Quaternion get_orientation() const;
        math::Matrix4 get_transform() const;
        float get_inv_mass() const;
        float get_mass() const;
        bool has_infinite_mass() const;

        void integrate();
};

#endif  // RIGID_BODY_HPP
