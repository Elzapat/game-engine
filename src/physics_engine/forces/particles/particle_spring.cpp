#include "physics_engine/forces/particles/particle_spring.hpp"

ParticleSpring::ParticleSpring(std::shared_ptr<Particle> _other, float _k, float _rest_length) :
    other(_other),
    k(_k),
    rest_length(_rest_length) {}

ParticleSpring::~ParticleSpring() {}

void ParticleSpring::update_force(std::shared_ptr<Particle> particle) {
    math::Vector3 vector_between = particle->get_position() - other->get_position();
    float force_to_add = k * (rest_length - vector_between.norm());

    particle->add_force(vector_between.normalize() * force_to_add);
}
