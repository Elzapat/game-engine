#ifndef FORCE_GENERATOR_HPP
#define FORCE_GENERATOR_HPP

#include <memory>

#include "math/vector3.hpp"
#include "physics_engine/rigid_body.hpp"
#include "time.hpp"

class ForceGenerator {
    public:
        virtual void update_force(std::shared_ptr<RigidBody> rb) = 0;
};

class Gravity: public ForceGenerator {
    private:
        math::Vector3 gravity;

    public:
        Gravity(float gravity);
        virtual void update_force(std::shared_ptr<RigidBody> rb);
};

class Spring: public ForceGenerator {
    private:
        math::Vector3 connection_point_local;
        math::Vector3 other_connection_point_local;
        std::shared_ptr<RigidBody> other;

        float spring_constant;
        float rest_length;

    public:
        Spring(
            math::Vector3 conn_point,
            math::Vector3 other_conn_point,
            float k,
            float rest_length
        );
        virtual void update_force(std::shared_ptr<RigidBody> rb);
};

#endif  // FORCE_GENERATOR_HPP
