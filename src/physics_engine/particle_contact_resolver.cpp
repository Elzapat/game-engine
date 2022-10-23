#include "../../include/physics_engine/particle_contact_resolver.hpp"

ParticleContactResolver::ParticleContactResolver(unsigned int _max_iterations) :
    max_iterations(_max_iterations) {}

ParticleContactResolver::~ParticleContactResolver() {}

void ParticleContactResolver::resolve_contacts(std::vector<ParticleContact> contacts) {
    if (contacts.empty()) {
        return;
    }

    this->max_iterations = contacts.size() * 2;

    // Loop until max iterations is reached or the smallest relative velocityis
    // is higher than 0, meaning all contacts have been resolved
    for (int iterations = 0; iterations < max_iterations; iterations++) {
        /* std::sort(contacts.begin(), contacts.end(), [](ParticleContact c1, ParticleContact c2) { */
        /*     return c1.separating_velocity() < c2.separating_velocity(); */
        /* }); */
        /* smallest_rel_vel = contacts.back().separating_velocity(); */
        float smallest_sep_vel = std::numeric_limits<float>::max();
        int contact_to_resolve_idx = contacts.size();

        for (int i = 0; i < contacts.size(); i++) {
            float sep_vel = contacts[i].separating_velocity();
            if (sep_vel < smallest_sep_vel && (sep_vel < 0.0f || contacts[i].penetration > 0)) {
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
