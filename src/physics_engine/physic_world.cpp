#include "physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : particle_contact_resolver() {
    std::shared_ptr<RigidBody> rb = std::make_shared<RigidBody>();
    /* rb->set_orientation(math::Quaternion(1.0f, 0.5f, 1.0f, 2.0f)); */
    /* rb->set_angular_velocity(math::Vector3(20.1f, 20.1f, 20.1f)); */
    rb->set_mass(50.0f);
    // rb->set_linear_velocity(math::Vector3(0.5f, 1.0f, 2.0f));

    std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();
    rb2->set_posisition(math::Vector3(0.0f, -10.0f, 0.0f));
    rb2->set_mass(50.0f);

    std::unique_ptr<Spring> spring = std::make_unique<Spring>(
        math::Vector3(0.0f, 0.0f, 0.0f),
        rb2,
        math::Vector3(-0.0f, -0.0f, -0.0f),
        50.0f,
        3.0f
    );
    std::unique_ptr<Gravity> gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));

    this->force_registry.add_entry(rb, std::move(spring));
    this->force_registry.add_entry(rb, std::move(gravity));

    this->add_rigid_body(rb);
    this->add_rigid_body(rb2);
}

void PhysicWorld::update() {
    std::vector<ParticleContact> contacts;

    this->particle_force_registry.update();
    this->force_registry.update();

    for (auto& contact_generator : this->particle_contact_generators) {
        contact_generator->add_contact(contacts);
    }

    this->particle_contact_resolver.resolve_contacts(contacts);

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
