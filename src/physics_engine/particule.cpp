#include "../../include/physics_engine/particule.hpp"

Particule::Particule() {}
Particule::~Particule() {}

void Particule::set_position(Vector3D const& position) {
    this->position = position;
}

void Particule::set_velocity(Vector3D const& velocity) {
    this->velocity = velocity;
}

void Particule::set_acceleration(Vector3D const& acceleration) {
    this->acceleration = acceleration;
}

void Particule::set_inv_mass(float const& inv_mass) {
    this->inv_mass = inv_mass;
}

void Particule::set_damping(float const& damping) {
    this->damping = damping;
}

Vector3D Particule::get_position() const {
    return this->position;
}

Vector3D Particule::get_velocity() const {
    return this->velocity;
}

Vector3D Particule::get_acceleration() const {
    return this->acceleration;
}

float Particule::get_inv_mass() const {
    return this->inv_mass;
}

float Particule::get_damping() const {
    return this->damping;
}

void Particule::integrate(float dt) {
    /* this->position = (this->acceleration) * pow(time_delta, 2) * 0.5 + this->velocity * time_delta */
    /*     + this->position; */
    /* this->velocity = (this->acceleration) * time_delta + this->velocity; */

    this->position += this->velocity * dt;
    this->velocity = (this->velocity * this->damping) + (this->acceleration * dt);
}
