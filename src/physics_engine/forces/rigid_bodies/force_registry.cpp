#include "physics_engine/forces/rigid_bodies/force_registry.hpp"

ForceRegistry::ForceRegistry() {}

ForceRegistry::~ForceRegistry() {}

void ForceRegistry::add_entry(
    std::shared_ptr<RigidBody> rigid_body,
    std::shared_ptr<ForceGenerator> force_generator
) {
    ForceEntry entry;
    entry.rigid_body = rigid_body;
    entry.force_generator = force_generator;

    this->registry.push_back(entry);
}

void ForceRegistry::update() {
    for (auto entry : this->registry) {
        entry.force_generator->update_force(entry.rigid_body);
    }
}
