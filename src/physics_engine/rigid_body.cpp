#include "physics_engine/rigid_body.hpp"

RigidBody::RigidBody() {}

RigidBody::~RigidBody() {}

void RigidBody::add_force(const math::Vector3& force) {
    this->forces += force;
}

void RigidBody::add_force_at_world_point(const math::Vector3& force, math::Vector3 point) {
    point -= this->position;

    this->forces += force;
    this->torques += point.cross(force);
}

void RigidBody::add_force_at_local_point(const math::Vector3& force, math::Vector3 point) {
    this->add_force_at_world_point(force, this->transform * point);
}

void RigidBody::apply_impulse(const math::Vector3& impulse) {
    this->linear_velocity += impulse;
}

math::Vector3 RigidBody::get_point_in_world_space(const math::Vector3& point) {
    return this->transform * point;
}

void RigidBody::set_posisition(const math::Vector3 pos) {
    this->position = pos;
}

void RigidBody::set_linear_velocity(const math::Vector3 vel) {
    this->linear_velocity = vel;
}

void RigidBody::set_linear_damping(float linear_damping) {
    this->linear_damping = linear_damping;
}

void RigidBody::set_angular_velocity(const math::Vector3 vel) {
    this->angular_velocity = vel;
}

void RigidBody::set_angular_damping(const float angular_damping) {
    this->angular_damping = angular_damping;
}

void RigidBody::set_rotation(const math::Vector3 rot) {
    this->rotation = rot;
}

void RigidBody::set_orientation(const math::Quaternion orientation) {
    this->orientation = orientation;
}

void RigidBody::set_transform(const math::Matrix4 transform) {
    this->transform = transform;
}

void RigidBody::set_inv_mass(const float inv_mass) {
    this->inv_mass = inv_mass;
}

void RigidBody::set_mass(const float mass) {
    this->inv_mass = 1.0f / mass;
}

math::Vector3 RigidBody::get_position() const {
    return this->position;
}

math::Vector3 RigidBody::get_linear_velocity() const {
    return this->linear_velocity;
}

float RigidBody::get_linear_damping() const {
    return this->linear_damping;
}

math::Vector3 RigidBody::get_angular_velocity() const {
    return this->angular_velocity;
}

float RigidBody::get_angular_damping() const {
    return this->angular_damping;
}

math::Vector3 RigidBody::get_rotation() const {
    return this->rotation;
}

math::Quaternion RigidBody::get_orientation() const {
    return this->orientation;
}

math::Matrix4 RigidBody::get_transform() const {
    return this->transform;
}

float RigidBody::get_inv_mass() const {
    return this->inv_mass;
}

float RigidBody::get_mass() const {
    return 1.0f / this->inv_mass;
}

bool RigidBody::has_infinite_mass() const {
    return this->inv_mass == 0.0f;
}

void RigidBody::compute_derived_data() {
    this->orientation = this->orientation.rotate(this->rotation).normalize();

    this->transform = this->transform.translate(this->position).rotate(this->orientation);
}

void RigidBody::integrate() {
    float dt = Time::delta_time();

    // this->orientation.update_by_angular_velocity(this->rotation);

    this->compute_derived_data();

    this->linear_velocity *= std::pow(this->linear_damping, dt);
    this->rotation *= std::pow(this->angular_damping, dt);

    this->linear_acceleration = this->inv_mass * this->forces;
    this->linear_velocity += this->linear_acceleration * dt;
    this->position += this->linear_velocity * dt;

    this->angular_acceleration = this->inv_mass * this->torques;
    this->rotation += this->angular_velocity * dt;
    std::cout << this->rotation << std::endl;

    this->forces = math::Vector3();
    this->torques = math::Vector3();
}
