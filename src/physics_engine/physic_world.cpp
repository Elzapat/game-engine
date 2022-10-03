#include "../../include/physics_engine/physic_world.hpp"

void PhysicWorld::update(float dt) {
    for (auto& particle : this->particles) {
        particle.integrate(dt);
    }
}

void PhysicWorld::add_particle(const Particle particule) {
    this->particles.push_back(particule);
}

std::vector<Particle> PhysicWorld::get_particles() const {
    return this->particles;
}

std::vector<Particle>& PhysicWorld::get_particles_ref() {
    return this->particles;
}
