#include "../../include/physics_engine/particle_gravity.hpp"

ParticleGravity :: ParticleGravity(math::Vector3D _gravity) : gravity(_gravity) {}

ParticleGravity :: ~ParticleGravity() {}

void ParticleGravity::update_force(Particle* particle, float duration) {

    math::Vector3D new_acceleration = particle->get_acceleration() + gravity;

    particle->set_acceleration(new_acceleration);
}