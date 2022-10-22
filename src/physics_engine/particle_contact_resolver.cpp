#include "../../include/physics_engine/particle_contact_resolver.hpp"

ParticleContactResolver::ParticleContactResolver(unsigned int _max_iterations) :
    max_iterations(_max_iterations) {}

ParticleContactResolver::~ParticleContactResolver() {}

void ParticleContactResolver::resolve_contacts(std::vector<ParticleContact> contacts) {
    float smallest_rel_vel = std::numeric_limits<float>::max();

    // Loop until max iterations is reached or the smallest relative velocityis
    // is higher than 0, meaning all contacts have been resolved
    for (int iterations = 0; smallest_rel_vel > 0.0f && iterations < max_iterations; iterations++) {
        std::sort(contacts.begin(), contacts.end(), [](ParticleContact c1, ParticleContact c2) {
            return c1.relative_velocity() < c2.relative_velocity();
        });
        smallest_rel_vel = contacts.back().relative_velocity();

        for (ParticleContact& contact : contacts) {
            contact.resolve();
        }
    }
}
