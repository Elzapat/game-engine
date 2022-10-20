#include "../../include/physics_engine/particle_spring.hpp"

ParticleSpring::ParticleSpring(Particle* _other, float _k, float _rest_length) :
    other(_other),
    k(_k),
    rest_length(_rest_length) {}

ParticleSpring::~ParticleSpring() {}

void ParticleSpring::update_force(Particle* particle) {
    math::Vector3D vector_between = particle->get_position() - other->get_position();
    float force_to_add = k * (rest_length - vector_between.norm());

    particle->add_force(vector_between.normalize() * force_to_add * Time::delta_time());
}
