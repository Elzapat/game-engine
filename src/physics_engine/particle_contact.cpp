#include "../../include/physics_engine/particle_contact.hpp"

ParticleContact :: ParticleContact(
    Particle* _particle,
    Particle* _other_particle,
    float _restitution,
    float _penetration
) : 
    particles[0](_particle),
    particles[1](_other_particle),
    restitution(_restitution),
    penetration(_penetration) {}

ParticleContact :: ~ParticleContact() {}

void ParticleContact :: resolveVelocity(float duration) {
    //TO_DO
}

void ParticleContact :: resolveInterpenetration(float duration) {
    //TO_DO
}

void ParticleContact :: resolve(float duration) {
    resolveInterpenetration(duration);
    resolveVelocity(duration);
}

float ParticleContact :: calculateSeparatingVelocity() {
    math::Vector3D vector = particles[0]->get_velocity() - particles[1]->get_velocity();
    return vector.norm();
}
