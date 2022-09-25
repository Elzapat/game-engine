#include "../../include/physics_engine/physic_world.hpp"

void PhysicWorld::update(float dt) {
    for (auto& particule : this->particules) {
        particule.integrate(dt);
    }
}

void PhysicWorld::add_particule(const Particule particule) {
    this->particules.push_back(particule);
}

std::vector<Particule> PhysicWorld::get_particules() const {
    return this->particules;
}

std::vector<Particule>& PhysicWorld::get_particules_ref() {
    return this->particules;
}
