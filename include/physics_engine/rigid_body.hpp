#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <cmath>
#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include "../math/vector3.hpp"

namespace math {
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
            math::Matrix43 transform;
        
            void compute_derived_data();

        public:
            RigidBody();
            RigidBody(
                math::Vector3 pos,
                math::Vector3 vel,
                math::Vector3 rot,
                math::Quaternion orientation,
                math::Matrix43 transform,
                float inv_mass,
                float linear_damping
            );
            ~RigidBody();

            void set_posisition(math::Vector3 pos);
            void set_velocity(math::Vector3 vel);
            void set_rotation(math::Vector3 rot);
            void set_orientation(math::Quaternion orientation);
            void set_transform(math::Matrix43 transform);
            void set_inv_mass(float inv_mass);
            void set_linear_damping(float linear_damping);

            math::Vector3 get_position();
            math::Vector3 get_velocity();
            math::Vector3 get_rotation();
            math::Quaternion get_orientation();
            math::Matrix43 get_transform();
            float get_inv_mass();
            float get_linear_damping();

            void integrate();
    };
}

#endif // RIGID_BODY_HPP