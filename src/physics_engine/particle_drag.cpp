#include "../../include/physics_engine/particle_drag.hpp"

ParticleDrag::ParticleDrag(float _k1 = 1 , float _k2 = 1) : k1(_k1), k2(_k2) {}
ParticleDrag::~ParticleDrag() {}

void ParticleDrag::update_force(Particle* particle, float dt) {
};