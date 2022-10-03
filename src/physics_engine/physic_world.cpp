#include "../../include/physics_engine/physic_world.hpp"

void PhysicWorld::update(float dt) {
    for (auto& particule : this->particules) {
        particule.integrate(dt);
    }
}

void PhysicWorld::add_particule(const Particle particule) {
    this->particules.push_back(particule);
}

std::vector<Particle> PhysicWorld::get_particules() const {
    return this->particules;
}

std::vector<Particle>& PhysicWorld::get_particules_ref() {
    return this->particules;
}
