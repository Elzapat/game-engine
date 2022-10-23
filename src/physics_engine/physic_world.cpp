#include "../../include/physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : contact_resolver(20) {
    std::shared_ptr<Particle> p1 = std::make_shared<Particle>();
    std::shared_ptr<Particle> p2 = std::make_shared<Particle>();
    p1->set_mass(50.0f);
    p2->set_mass(50.0f);

    std::shared_ptr<ParticleSpring> spring = std::make_shared<ParticleSpring>(p2, 40.0f, 3.5f);
    std::shared_ptr<ParticleSpring> spring2 = std::make_shared<ParticleSpring>(p1, 40.0f, 3.5f);
    std::shared_ptr<ParticleDrag> drag = std::make_shared<ParticleDrag>(0.47f, 0.0f);

    p1->set_position(math::Vector3D(5.0f, 0.0f, 0.0f));

    this->force_registry.add_entry(p1, spring);
    this->force_registry.add_entry(p2, spring2);
    this->force_registry.add_entry(p1, drag);
    this->force_registry.add_entry(p2, drag);

    this->particles.push_back(p1);
    this->particles.push_back(p2);

    const float RADIUS = 1.0f;
    auto contact = std::make_unique<NaiveParticleContactGenerator>(this->particles, RADIUS);

    this->contact_generators.push_back(std::move(contact));
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
}

void PhysicWorld::add_particle(const Particle particle) {
    this->particles.push_back(std::make_shared<Particle>(particle));
}

void PhysicWorld::add_particle(std::shared_ptr<Particle> particle) {
    this->particles.push_back(particle);
}

std::vector<std::shared_ptr<Particle>> PhysicWorld::get_particles() const {
    return this->particles;
}

std::vector<std::shared_ptr<Particle>>& PhysicWorld::get_particles_ref() {
    return this->particles;
}
