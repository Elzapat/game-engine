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
    this->add_force_at_world_point(force, point.transform(this->transform));
}

void RigidBody::apply_impulse(const math::Vector3& impulse) {
    this->velocity += impulse * inv_mass;
}

void RigidBody::apply_torque_impulse(const math::Vector3& torque) {
    this->rotation += torque.transform(this->inv_inertia_tensor_world);
}

math::Vector3 RigidBody::get_point_in_world_space(const math::Vector3& point) {
    return point.transform(this->transform);
}

math::Matrix3 RigidBody::transform_inertia_tensor(
    const math::Quaternion& orientation,
    const math::Matrix3& inv_inertia_tensor,
    const math::Matrix4& transform
) {
    math::Matrix3 inv_inertia_tensor_world;
    std::array<float, 12> transform_values = transform.get_values();
    std::array<float, 9> iit_values = inv_inertia_tensor.get_values();
    std::array<float, 9>& iit_world_values = inv_inertia_tensor_world.get_values_ref();

    float t4 = transform_values[0] * iit_values[0] + transform_values[1] * iit_values[3]
        + transform_values[2] * iit_values[6];
    float t9 = transform_values[0] * iit_values[1] + transform_values[1] * iit_values[4]
        + transform_values[2] * iit_values[7];
    float t14 = transform_values[0] * iit_values[2] + transform_values[1] * iit_values[5]
        + transform_values[2] * iit_values[8];
    float t28 = transform_values[4] * iit_values[0] + transform_values[5] * iit_values[3]
        + transform_values[6] * iit_values[6];
    float t33 = transform_values[4] * iit_values[1] + transform_values[5] * iit_values[4]
        + transform_values[6] * iit_values[7];
    float t38 = transform_values[4] * iit_values[2] + transform_values[5] * iit_values[5]
        + transform_values[6] * iit_values[8];
    float t52 = transform_values[8] * iit_values[0] + transform_values[9] * iit_values[3]
        + transform_values[10] * iit_values[6];
    float t57 = transform_values[8] * iit_values[1] + transform_values[9] * iit_values[4]
        + transform_values[10] * iit_values[7];
    float t62 = transform_values[8] * iit_values[2] + transform_values[9] * iit_values[5]
        + transform_values[10] * iit_values[8];

    iit_world_values[0] =
        t4 * transform_values[0] + t9 * transform_values[1] + t14 * transform_values[2];
    iit_world_values[1] =
        t4 * transform_values[4] + t9 * transform_values[5] + t14 * transform_values[6];
    iit_world_values[2] =
        t4 * transform_values[8] + t9 * transform_values[9] + t14 * transform_values[10];
    iit_world_values[3] =
        t28 * transform_values[0] + t33 * transform_values[1] + t38 * transform_values[2];
    iit_world_values[4] =
        t28 * transform_values[4] + t33 * transform_values[5] + t38 * transform_values[6];
    iit_world_values[5] =
        t28 * transform_values[8] + t33 * transform_values[9] + t38 * transform_values[10];
    iit_world_values[6] =
        t52 * transform_values[0] + t57 * transform_values[1] + t62 * transform_values[2];
    iit_world_values[7] =
        t52 * transform_values[4] + t57 * transform_values[5] + t62 * transform_values[6];
    iit_world_values[8] =
        t52 * transform_values[8] + t57 * transform_values[9] + t62 * transform_values[10];

    return inv_inertia_tensor_world;
}

void RigidBody::set_position(const math::Vector3 pos) {
    this->position = pos;
}

void RigidBody::set_velocity(const math::Vector3 vel) {
    this->velocity = vel;
}

void RigidBody::set_linear_damping(float linear_damping) {
    this->linear_damping = linear_damping;
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

void RigidBody::set_inertia_tensor(const math::Matrix3& inertia_tensor) {
    this->inv_inertia_tensor = inertia_tensor.inverse();
}

math::Vector3 RigidBody::get_position() const {
    return this->position;
}

math::Vector3 RigidBody::get_velocity() const {
    return this->velocity;
}

math::Vector3 RigidBody::get_acceleration() const {
    return this->linear_acceleration;
}

float RigidBody::get_linear_damping() const {
    return this->linear_damping;
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
    this->orientation = this->orientation.normalize();
    this->transform.set_translation(this->position).set_orientation(this->orientation);

    this->inv_inertia_tensor_world = this->transform_inertia_tensor(
        this->orientation,
        this->inv_inertia_tensor,
        this->transform
    );
}

void RigidBody::integrate() {
    float dt = Time::delta_time();

    this->linear_acceleration = this->inv_mass * this->forces;
    this->angular_acceleration = this->torques.transform(this->inv_inertia_tensor_world);

    this->velocity += this->linear_acceleration * dt;
    this->rotation += this->angular_acceleration * dt;

    this->velocity *= std::pow(this->linear_damping, dt);
    this->rotation *= std::pow(this->angular_damping, dt);

    this->position += this->velocity * dt;
    this->orientation += this->rotation * dt;

    this->compute_derived_data();

    this->forces = math::Vector3();
    this->torques = math::Vector3();
}
