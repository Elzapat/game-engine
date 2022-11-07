#include "physics_engine/forces/rigid_bodies/force_generator.hpp"

Gravity::Gravity(math::Vector3 _gravity) : gravity(_gravity) {}

void Gravity::update_force(std::shared_ptr<RigidBody> rb) {
    if (rb->has_infinite_mass()) {
        return;
    }

    rb->add_force(this->gravity * rb->get_mass());
}

Spring::Spring(
    math::Vector3 conn_point,
    std::shared_ptr<RigidBody> _other,
    math::Vector3 other_conn_point,
    float k,
    float _rest_length
) :
    connection_point_local(conn_point),
    other(_other),
    other_connection_point_local(other_conn_point),
    spring_constant(k),
    rest_length(_rest_length) {}

void Spring::update_force(std::shared_ptr<RigidBody> rb) {
    math::Vector3 first_end = rb->get_point_in_world_space(this->connection_point_local);
    math::Vector3 second_end =
        this->other->get_point_in_world_space(this->other_connection_point_local);

    math::Vector3 force = first_end - second_end;
    float magnitude = std::abs(force.norm() - this->rest_length) * spring_constant;

    rb->add_force_at_world_point(force.normalize() * -magnitude, first_end);
}
