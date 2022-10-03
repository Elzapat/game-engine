#include "../../include/physics_engine/particle_anchored_spring.hpp"

ParticleAnchoredSpring :: ParticleAnchoredSpring(
    math::Vector3D _anchor,
    float _k,
    float _rest_length
) : 
    anchor(_anchor),
    k(_k),
    rest_length(_rest_length) {}


ParticleAnchoredSpring :: ~ParticleAnchoredSpring() {}

void ParticleAnchoredSpring ::update_force(Particle* particle, float duration) {

    math::Vector3D vector_between = particle->get_position() - anchor;

    float force_to_add = k * ( rest_length - vector_between.norm() );

    vector_between.normalize();

    math::Vector3D new_acceleration = particle->get_acceleration() + vector_between * force_to_add;

    particle->set_acceleration(new_acceleration);
}