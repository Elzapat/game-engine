#include "../../include/physics_engine/particle.hpp"

Particle::Particle() :
    position(math::Vector3D()),
    velocity(math::Vector3D()),
    acceleration(math::Vector3D()),
    forces(math::Vector3D()),
    inv_mass(0.0f) {}

Particle::Particle(math::Vector3D pos, math::Vector3D vel, math::Vector3D accel, float _inv_mass) :
    position(pos),
    velocity(vel),
    acceleration(accel),
    forces(math::Vector3D()),
    inv_mass(_inv_mass) {}

Particle::~Particle() {}

void Particle::set_position(const math::Vector3D position) {
    this->position = position;
}

void Particle::set_velocity(const math::Vector3D velocity) {
    this->velocity = velocity;
}

void Particle::add_velocity(math::Vector3D delta_vel) {
    this->velocity += delta_vel;
}

void Particle::set_acceleration(const math::Vector3D acceleration) {
    this->acceleration = acceleration;
}

void Particle::set_inv_mass(const float inv_mass) {
    this->inv_mass = inv_mass;
}

void Particle::set_mass(const float mass) {
    this->inv_mass = 1.0f / mass;
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

float Particle::get_mass() const {
    return 1.0f / this->inv_mass;
}

math::Vector3D Particle::get_forces() const {
    return this->forces;
}

void Particle::add_force(math::Vector3D force) {
    this->forces += force;
}

void Particle::integrate() {
    float dt = Time::delta_time();

    this->acceleration = this->forces;
    this->velocity += this->acceleration * dt;
    this->position += this->velocity * dt;

    this->forces = math::Vector3D(0.0f, 0.0f, 0.0f);
    this->acceleration = math::Vector3D(0.0f, 0.0f, 0.0f);
}
