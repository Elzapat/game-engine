#include "physics_engine/contacts/particles/naive_particle_contact_generator.hpp"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(
    std::vector<std::shared_ptr<Particle>> _particles,
    float _radius
) :
    radius(_radius),
    particles(_particles) {}

void NaiveParticleContactGenerator::add_contact(std::vector<ParticleContact>& contacts) const {
    for (auto p1_it = this->particles.begin(); p1_it != this->particles.end(); p1_it++) {
        for (auto p2_it = this->particles.begin(); p2_it != this->particles.end(); p2_it++) {
            if (p1_it == p2_it) {
                continue;
            }

            std::shared_ptr<Particle> p1 = *p1_it;
            std::shared_ptr<Particle> p2 = *p2_it;

            float penetration = (p1->get_position() - p2->get_position()).norm();

            if (penetration < 2.0f * this->radius) {
                contacts.push_back(ParticleContact(p1, p2, 0.3f, 2.0 * this->radius - penetration));
            }
        }
    }
}
