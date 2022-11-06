#include "physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : contact_resolver() {
    std::shared_ptr<RigidBody> rb = std::make_shared<RigidBody>();
    rb->set_orientation(math::Quaternion(1.0f, 0.5f, 1.0f, 2.0f));
    rb->set_angular_velocity(math::Vector3(20.1f, 20.1f, 20.1f));
    // rb->set_linear_velocity(math::Vector3(0.5f, 1.0f, 2.0f));

    this->add_rigid_body(rb);
}

void PhysicWorld::update() {
    std::vector<ParticleContact> contacts;

    this->force_registry.update();

    for (auto& contact_generator : this->contact_generators) {
        contact_generator->add_contact(contacts);
    }

    this->contact_resolver.resolve_contacts(contacts);

    for (auto& particle : this->particles) {
        particle->integrate();
    }

    for (auto& rigid_body : this->rigid_bodies) {
        rigid_body->integrate();
    }
}

void PhysicWorld::add_particle(const Particle particle) {
    this->particles.push_back(std::make_shared<Particle>(particle));
}

void PhysicWorld::add_particle(std::shared_ptr<Particle> particle) {
    this->particles.push_back(particle);
}

void PhysicWorld::add_rigid_body(const RigidBody rb) {
    this->rigid_bodies.push_back(std::make_shared<RigidBody>(rb));
}

void PhysicWorld::add_rigid_body(std::shared_ptr<RigidBody> rb) {
    this->rigid_bodies.push_back(rb);
}

std::vector<std::shared_ptr<Particle>> PhysicWorld::get_particles() const {
    return this->particles;
}

std::vector<std::shared_ptr<Particle>>& PhysicWorld::get_particles_ref() {
    return this->particles;
}

std::vector<std::shared_ptr<RigidBody>> PhysicWorld::get_rigid_bodies() const {
    return this->rigid_bodies;
}

std::vector<std::shared_ptr<RigidBody>>& PhysicWorld::get_rigid_bodies_ref() {
    return this->rigid_bodies;
}
