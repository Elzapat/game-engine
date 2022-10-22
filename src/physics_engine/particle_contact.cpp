#include "../../include/physics_engine/particle_contact.hpp"

ParticleContact::ParticleContact(
    std::shared_ptr<Particle> p1,
    std::shared_ptr<Particle> p2,
    float _restitution,
    float _penetration
) :
    particle1(p1),
    particle2(p2),
    restitution(_restitution),
    penetration(_penetration) {}

ParticleContact ::~ParticleContact() {}

void ParticleContact::resolve_velocity() {
    std::shared_ptr<Particle> p1 = this->particle1;
    std::shared_ptr<Particle> p2 = this->particle2;

    // Apply impulsion : k = ((e + 1)v_rel * n) / ((1 / m_1 + 1 / m_2)n * n)
    math::Vector3D k = (this->restitution + 1) * this->relative_velocity() * this->normal;
    k /= (p1->get_inv_mass() + p2->get_inv_mass());

    // v' = v ± k / m
    p1->set_velocity(p1->get_velocity() - k * p1->get_inv_mass());
    p2->set_velocity(p2->get_velocity() + k * p2->get_inv_mass());
}

void ParticleContact::resolve_interpenetration() {
    float p1_mass = this->particle1->get_mass();
    float p2_mass = this->particle2->get_mass();

    // Apply a delta to the position of the particles, factoring in their mass
    // Δp_a =  (m_b / (m_a + m_b))dn
    // Δp_b = -(m_a / (m_a + m_b))dn
    math::Vector3D delta_p1 = (p2_mass / (p1_mass + p2_mass)) * this->penetration * this->normal;
    math::Vector3D delta_p2 = -(p1_mass / (p1_mass + p2_mass)) * this->penetration * this->normal;

    this->particle1->add_velocity(delta_p1);
    this->particle2->add_velocity(delta_p2);
}

void ParticleContact::resolve() {
    this->resolve_interpenetration();
    this->resolve_velocity();
}

float ParticleContact::relative_velocity() {
    return (this->particle1->get_velocity() - this->particle2->get_velocity()).norm();
}
