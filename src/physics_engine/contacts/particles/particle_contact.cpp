#include "physics_engine/contacts/particles/particle_contact.hpp"

ParticleContact::ParticleContact(
    std::shared_ptr<Particle> p1,
    std::shared_ptr<Particle> p2,
    float _restitution,
    float _penetration
) :
    particle1(p1),
    particle2(p2),
    restitution(_restitution),
    penetration(_penetration),
    normal((p1->get_position() - p2->get_position()).normalize()) {}

ParticleContact ::~ParticleContact() {}

void ParticleContact::resolve_velocity() {
    float separating_velocity = this->separating_velocity();

    if (separating_velocity > 0.0f) {
        return;
    }

    float new_separating_velocity = -separating_velocity * this->restitution;

    math::Vector3 accel_caused_vel =
        this->particle1->get_acceleration() - this->particle2->get_acceleration();
    float accel_caused_sep_vel = accel_caused_vel.dot(this->normal) * Time::delta_time();

    if (accel_caused_sep_vel < 0.0f) {
        new_separating_velocity += this->restitution * accel_caused_sep_vel;

        if (new_separating_velocity < 0.0f) {
            new_separating_velocity = 0.0f;
        }
    }

    float total_inv_mass = this->particle1->get_inv_mass() + this->particle2->get_inv_mass();
    float delta_velocity = new_separating_velocity - separating_velocity;

    if (total_inv_mass <= 0.0f) {
        return;
    }

    float impulse = delta_velocity / total_inv_mass;

    this->particle1->apply_impulse(impulse * this->normal);
    this->particle2->apply_impulse(-impulse * this->normal);
}

void ParticleContact::resolve_interpenetration() {
    if (penetration <= 0.00f) {
        return;
    }

    float total_inv_mass = this->particle1->get_inv_mass() + this->particle2->get_inv_mass();

    if (total_inv_mass <= 0) {
        return;
    }

    math::Vector3 delta_position = this->normal * (this->penetration / total_inv_mass);

    math::Vector3 delta_p1 = delta_position * this->particle1->get_inv_mass();
    math::Vector3 delta_p2 = delta_position * -this->particle2->get_inv_mass();

    this->particle1->set_position(this->particle1->get_position() + delta_p1);
    this->particle2->set_position(this->particle2->get_position() + delta_p2);

    this->penetration = 0.0f;
}

void ParticleContact::resolve() {
    this->resolve_interpenetration();
    this->resolve_velocity();
}

math::Vector3 ParticleContact::relative_velocity() {
    return this->particle1->get_velocity() - this->particle2->get_velocity();
}

float ParticleContact::separating_velocity() {
    return this->relative_velocity().dot(this->normal);
}
