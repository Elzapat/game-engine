#include "physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : particle_contact_resolver() {
    this->octree = build_octree(math::Vector3(16.0f, 16.0f, 16.0f), 200.0f, 3);
}

void PhysicWorld::update(std::vector<Object>& objects) {
    this->particle_force_registry.update();
    this->force_registry.update();

    // Particle contacts detection and resolution
    {
        std::vector<ParticleContact> contacts;

        for (auto& contact_generator : this->particle_contact_generators) {
            contact_generator->add_contact(contacts);
        }

        this->particle_contact_resolver.resolve_contacts(contacts);
    }

    // Rigidbodie contacts detection and resolution
    {
        CollisionData collision_data;
        collision_data.friction = 0.0f;
        collision_data.restitution = 0.4f;

        std::vector<PossibleCollision> possible_collisions = this->octree->process(objects);

        for (PossibleCollision& possible_collision : possible_collisions) {
            this->collision_detector.check_collision(
                possible_collision.first->get_collision_volume(),
                possible_collision.second->get_collision_volume(),
                collision_data
            );
        }

        this->contact_resolver.iterations = collision_data.contacts.size() * 4;
        this->contact_resolver.resolve_contacts(collision_data.contacts);
    }

    for (Object& object : objects) {
        object.get_rigid_body()->integrate();
    }
}
