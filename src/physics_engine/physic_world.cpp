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
        // std::cout << "possible collisions:" << possible_collisions.size() << std::endl;

        std::vector<std::pair<size_t, size_t>> checked;

        // for (PossibleCollision& possible_collision : possible_collisions) {
        for (Object& o1 : objects) {
            for (Object& o2 : objects) {
                if (o1.get_rigid_body().get() == o2.get_rigid_body().get()) {
                    continue;
                }
                if (std::find_if(
                        checked.cbegin(),
                        checked.cend(),
                        [&](auto pair) {
                            return pair
                                == std::make_pair(
                                       (size_t)o1.get_rigid_body().get(),
                                       (size_t)o2.get_rigid_body().get()
                                )
                                || pair
                                == std::make_pair(
                                       (size_t)o2.get_rigid_body().get(),
                                       (size_t)o1.get_rigid_body().get()
                                );
                        }
                    )
                    != checked.cend()) {
                    continue;
                }

                checked.push_back(std::make_pair(
                    (size_t)o1.get_rigid_body().get(),
                    (size_t)o2.get_rigid_body().get()
                ));
                std::shared_ptr<Primitive> first_volume =
                    o1.get_rigid_body()->get_collision_volume();
                std::shared_ptr<Primitive> second_volume =
                    o2.get_rigid_body()->get_collision_volume();

                this->collision_detector
                    .check_collision(first_volume, second_volume, collision_data);

                if (first_volume && second_volume) {
                    // std::cout << "checking collisioin\n";
                    // first_volume->rigid_body = o1.get_rigid_body();
                    // second_volume->rigid_body = o2.get_rigid_body();
                }
            }
        }

        if (collision_data.contacts.size() > 0) {
            // std::cout << "collision_data contacts len: " << collision_data.contacts.size()
                      // << std::endl;
        }

        this->contact_resolver.iterations = collision_data.contacts.size() * 4;
        // this->contact_resolver.iterations = 2;
        this->contact_resolver.resolve_contacts(collision_data.contacts);

        // std::transform(possible_collisions.cbegin(), possible_collisions.cend(), possible_collisions.begin(), [](PossibleCollision possible_collision) {
        //     CollisionData collision_data;
        //     collision_data.
        // });
    }

    for (Object& object : objects) {
        object.get_rigid_body()->integrate();
    }
}
