#include "../../include/physics_engine/particle_gravity.hpp"

ParticleGravity::ParticleGravity(math::Vector3 _gravity) : gravity(_gravity) {}
ParticleGravity::~ParticleGravity() {}

void ParticleGravity::update_force(Particle* particle) {
    particle->add_force(this->gravity * Time::delta_time());
}
