#include "../../include/physics_engine/particule.hpp"

Particule::Particule() :
    position(math::Vector3D()),
    velocity(math::Vector3D()),
    acceleration(math::Vector3D()),
    inv_mass(0.0f),
    damping(0.9999f) {}

Particule::Particule(
    math::Vector3D pos,
    math::Vector3D vel,
    math::Vector3D accel,
    float _inv_mass,
    float _damping
) :
    position(pos),
    velocity(vel),
    acceleration(accel),
    inv_mass(_inv_mass),
    damping(_damping) {}

Particule::~Particule() {}

void Particule::set_position(math::Vector3D const& position) {
    this->position = position;
}

void Particule::set_velocity(math::Vector3D const& velocity) {
    this->velocity = velocity;
}

void Particule::set_acceleration(math::Vector3D const& acceleration) {
    this->acceleration = acceleration;
}

void Particule::set_inv_mass(float const& inv_mass) {
    this->inv_mass = inv_mass;
}

void Particule::set_damping(float const& damping) {
    this->damping = damping;
}

math::Vector3D Particule::get_position() const {
    return this->position;
}

math::Vector3D Particule::get_velocity() const {
    return this->velocity;
}

math::Vector3D Particule::get_acceleration() const {
    return this->acceleration;
}

float Particule::get_inv_mass() const {
    return this->inv_mass;
}

float Particule::get_damping() const {
    return this->damping;
}

void Particule::integrate(float dt) {
    this->position += this->velocity * dt;
    this->velocity += (this->velocity * this->damping - this->velocity) * dt;
    this->velocity += this->acceleration * dt;
}
