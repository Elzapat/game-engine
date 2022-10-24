#include "../../include/physics_engine/particle_cable.hpp"

ParticleCable::ParticleCable(
    Particle* particle_1,
    Particle* particle_2,
    float _max_lenght
    float _restitution
) :
    max_lenght(_max_lenght),
    restitution(_restitution) {
        particles[0] = particle_1;
        particles[1] = particle_2;
    }

ParticleCable::~ParticleCable() {}

void ParticleContact::add_contact(std::vector<ParticleContact>& contacts) {
    float difference = this->currentLenght() - this->maxLenght;
    if(difference < 0) {
        contacts.push_back(ParticleContact(p1, p2, this->restitution, difference));
    }
}