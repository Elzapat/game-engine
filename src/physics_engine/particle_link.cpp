#include "../../include/physics_engine/particle_link.hpp"

ParticleLink::ParticleLink(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2) :
    particle1(p1),
    particle2(p2) {}

ParticleLink::~ParticleLink() {}

void ParticleLink::add_contact([[maybe_unused]] std::vector<ParticleContact>& contacts) {}

float ParticleLink::current_length() {
    return (this->particle1->get_position() - this->particle2->get_position()).norm();
}
