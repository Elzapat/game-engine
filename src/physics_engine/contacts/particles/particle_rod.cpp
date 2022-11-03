#include "physics_engine/contacts/particles/particle_rod.hpp"

ParticleRod::ParticleRod(
    std::shared_ptr<Particle> p1,
    std::shared_ptr<Particle> p2,
    float _length
) :
    ParticleLink(p1, p2),
    length(_length) {}

ParticleRod::~ParticleRod() {}

void ParticleRod::add_contact(std::vector<ParticleContact>& contacts) {
    float difference = this->current_length() - this->length;
    if (difference != 0) {
        contacts.push_back(ParticleContact(this->particle1, this->particle2, 0, difference));
    }
}
