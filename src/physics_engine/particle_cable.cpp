#include "../../include/physics_engine/particle_cable.hpp"

ParticleCable::ParticleCable(
    std::shared_ptr<Particle> p1,
    std::shared_ptr<Particle> p2,
    float _max_length,
    float _restitution
) :
    ParticleLink(p1, p2),
    max_length(_max_length),
    restitution(_restitution) {}

ParticleCable::~ParticleCable() {}

void ParticleCable::add_contact(std::vector<ParticleContact>& contacts) {
    float difference = this->current_length() - this->max_length;

    if (difference < 0) {
        contacts.push_back(
            ParticleContact(this->particle1, this->particle2, this->restitution, difference)
        );
    }
}
