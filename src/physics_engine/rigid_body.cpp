#include "physics_engine/rigid_body.hpp"

RigidBody::RigidBody() {}

RigidBody::RigidBody(
    math::Vector3 pos,
    math::Vector3 vel,
    math::Vector3 rot,
    math::Quaternion orientation,
    math::Matrix4 transform,
    float inv_mass,
    float linear_damping
) :
    inv_mass(inv_mass),
    linear_damping(linear_damping),
    position(pos),
    velocity(vel),
    orientation(orientation),
    rotation(rot),
    transform(transform) {}

RigidBody::~RigidBody() {}

void RigidBody::set_posisition(math::Vector3 pos) {
    this->position = pos;
}

void RigidBody::set_velocity(math::Vector3 vel) {
    this->velocity = vel;
}

void RigidBody::set_rotation(math::Vector3 rot) {
    this->rotation = rot;
}

void RigidBody::set_orientation(math::Quaternion orientation) {
    this->orientation = orientation;
}

void RigidBody::set_transform(math::Matrix4 transform) {
    this->transform = transform;
}

void RigidBody::set_inv_mass(float inv_mass) {
    this->inv_mass = inv_mass;
}

void RigidBody::set_linear_damping(float linear_damping) {
    this->linear_damping = linear_damping;
}

math::Vector3 RigidBody::get_position() {
    return this->position;
}

math::Vector3 RigidBody::get_velocity() {
    return this->velocity;
}

math::Vector3 RigidBody::get_rotation() {
    return this->rotation;
}

math::Quaternion RigidBody::get_orientation() {
    return this->orientation;
}

math::Matrix4 RigidBody::get_transform() {
    return this->transform;
}

float RigidBody::get_inv_mass() {
    return this->inv_mass;
}

float RigidBody::get_linear_damping() {
    return this->linear_damping;
}

void RigidBody::compute_derived_data() {
    this->orientation = this->orientation.normalize();
    this->transform = this->transform.translate(this->velocity);
    this->transform = this->transform.rotate(this->rotation);
}

void RigidBody::integrate() {
    float dt = Time::delta_time();

    this->orientation.update_by_angular_velocity(this->rotation);

    this->compute_derived_data();

    this->position += this->position * dt;
    this->velocity *= this->linear_damping / dt;
}
