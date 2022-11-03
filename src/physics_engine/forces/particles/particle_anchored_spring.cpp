#include "physics_engine/forces/particles/particle_anchored_spring.hpp"

ParticleAnchoredSpring::ParticleAnchoredSpring(
    math::Vector3 _anchor,
    float _k,
    float _rest_length
) :
    anchor(_anchor),
    k(_k),
    rest_length(_rest_length) {}

ParticleAnchoredSpring::~ParticleAnchoredSpring() {}

void ParticleAnchoredSpring::update_force(std::shared_ptr<Particle> particle) {
    math::Vector3 vector_between = particle->get_position() - this->anchor;
    float force_to_add = k * (this->rest_length - vector_between.norm());

    particle->add_force(vector_between.normalize() * force_to_add * Time::delta_time());
}
