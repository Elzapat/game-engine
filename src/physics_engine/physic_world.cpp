#include "../../include/physics_engine/physic_world.hpp"

void PhysicWorld::update(float dt) {
    for (auto& particule : this->particules) {
        particule.integrate(dt);
    }
}
