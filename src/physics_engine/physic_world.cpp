#include "physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : particle_contact_resolver() {}

void PhysicWorld::update(std::vector<Object>& objects) {
    std::vector<ParticleContact> contacts;

    this->particle_force_registry.update();
    this->force_registry.update();

    for (auto& contact_generator : this->particle_contact_generators) {
        contact_generator->add_contact(contacts);
    }

    this->particle_contact_resolver.resolve_contacts(contacts);

    for (Object& object : objects) {
        object.get_rigid_body()->integrate();
    }
}
