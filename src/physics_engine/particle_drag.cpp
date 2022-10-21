#include "../../include/physics_engine/particle_drag.hpp"

ParticleDrag::ParticleDrag(float _k1, float _k2) : k1(_k1), k2(_k2) {}
ParticleDrag::~ParticleDrag() {}

void ParticleDrag::update_force(std::shared_ptr<Particle> particle) {
    math::Vector3D velocity = particle->get_velocity();
    float velocity_norm = velocity.norm();

    float drag = velocity_norm * this->k1 + velocity_norm * velocity_norm * this->k2;
    particle->add_force(-velocity.normalize() * drag);
};
