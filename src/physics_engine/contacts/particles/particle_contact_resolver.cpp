#include "physics_engine/contacts/particles/particle_contact_resolver.hpp"

ParticleContactResolver::ParticleContactResolver(uint32_t _max_iterations) :
    max_iterations(_max_iterations) {}

ParticleContactResolver::~ParticleContactResolver() {}

void ParticleContactResolver::resolve_contacts(std::vector<ParticleContact> contacts) {
    if (contacts.empty()) {
        return;
    }

    this->max_iterations = contacts.size() * 2;

    // Loop until max iterations is reached or the smallest relative velocityis
    // is higher than 0, meaning all contacts have been resolved
    for (uint32_t iterations = 0; iterations < max_iterations; iterations++) {
        float smallest_sep_vel = std::numeric_limits<float>::max();
        size_t contact_to_resolve_idx = contacts.size();

        for (size_t i = 0; i < contacts.size(); i++) {
            float sep_vel = contacts[i].separating_velocity();
            if (sep_vel < smallest_sep_vel && (sep_vel < 0.0f || contacts[i].penetration > 0.0f)) {
                smallest_sep_vel = contacts[i].separating_velocity();
                contact_to_resolve_idx = i;
            }
        }

        if (contact_to_resolve_idx == contacts.size()) {
            break;
        }

        contacts[contact_to_resolve_idx].resolve();
    }
}
