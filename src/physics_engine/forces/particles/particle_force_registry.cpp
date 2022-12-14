#include "physics_engine/forces/particles/particle_force_registry.hpp"

ParticleForceRegistry::ParticleForceRegistry() {};
ParticleForceRegistry::~ParticleForceRegistry() {};

void ParticleForceRegistry::add_entry(
    std::shared_ptr<Particle> particle,
    std::shared_ptr<ParticleForceGenerator> force_generator
) {
    ParticleForceEntry pf_entry;
    pf_entry.particle = particle;
    pf_entry.force_generator = force_generator;

    this->registry.push_back(pf_entry);
}

void ParticleForceRegistry::remove_entry(
    std::shared_ptr<Particle> particle,
    std::shared_ptr<ParticleForceGenerator> force_generator
) {
    std::remove_if(
        this->registry.begin(),
        this->registry.end(),
        [&](ParticleForceEntry const& registry) {
            return registry.particle == particle && registry.force_generator == force_generator;
        }
    );
}

void ParticleForceRegistry::update() {
    for (auto entry : this->registry) {
        entry.force_generator->update_force(entry.particle);
    }
}
