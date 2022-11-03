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
        float inv_mass;
        float linear_damping;
        math::Vector3 position;
        math::Vector3 velocity;
        math::Quaternion orientation;
        math::Vector3 rotation;
        math::Matrix4 transform;

        void compute_derived_data();

    public:
        RigidBody();
        RigidBody(
            math::Vector3 pos,
            math::Vector3 vel,
            math::Vector3 rot,
            math::Quaternion orientation,
            math::Matrix4 transform,
            float inv_mass,
            float linear_damping
        );
        ~RigidBody();

        void set_posisition(math::Vector3 pos);
        void set_velocity(math::Vector3 vel);
        void set_rotation(math::Vector3 rot);
        void set_orientation(math::Quaternion orientation);
        void set_transform(math::Matrix4 transform);
        void set_inv_mass(float inv_mass);
        void set_linear_damping(float linear_damping);

        math::Vector3 get_position();
        math::Vector3 get_velocity();
        math::Vector3 get_rotation();
        math::Quaternion get_orientation();
        math::Matrix4 get_transform();
        float get_inv_mass();
        float get_linear_damping();

        void integrate();
};

#endif  // RIGID_BODY_HPP
