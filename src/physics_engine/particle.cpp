#include "../../include/physics_engine/particle.hpp"

Particle::Particle() :
    position(math::Vector3D()),
    velocity(math::Vector3D()),
    acceleration(math::Vector3D()),
    inv_mass(0.0f),
    damping(0.9999f) {}

Particle::Particle(
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

Particle::~Particle() {}

void Particle::set_position(math::Vector3D const position) {
    this->position = position;
}

void Particle::set_velocity(math::Vector3D const velocity) {
    this->velocity = velocity;
}

void Particle::set_acceleration(math::Vector3D const acceleration) {
    this->acceleration = acceleration;
}

void Particle::set_inv_mass(float const inv_mass) {
    this->inv_mass = inv_mass;
}

void Particle::set_damping(float const damping) {
    this->damping = damping;
}

void Particle::set_forces(math::Vector3D forces) {
    this->forces = forces;
}

math::Vector3D Particle::get_position() const {
    return this->position;
}

math::Vector3D Particle::get_velocity() const {
    return this->velocity;
}

math::Vector3D Particle::get_acceleration() const {
    return this->acceleration;
}

float Particle::get_inv_mass() const {
    return this->inv_mass;
}

float Particle::get_damping() const {
    return this->damping;
}

math::Vector3D Particle::get_forces() const {
    return this->forces;
}

void Particle::add_force(math::Vector3D force) {
    this->forces += force;
}

void Particle::integrate(float dt) {
    this->acceleration = this->forces;

    this->position += this->velocity * dt;
    this->velocity += (this->velocity * this->damping - this->velocity) * dt;
    this->velocity += this->acceleration * dt;

    this->forces = math::Vector3D(0.0f, 0.0f, 0.0f);
    this->acceleration = math::Vector3D(0.0f, 0.0f, 0.0f);
}
