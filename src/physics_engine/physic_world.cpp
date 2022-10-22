#include "../../include/physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() {
    std::shared_ptr<Particle> p1 = std::make_shared<Particle>();
    std::shared_ptr<Particle> p2 = std::make_shared<Particle>();

    std::shared_ptr<ParticleSpring> spring = std::make_shared<ParticleSpring>(p2, 20.0f, 2.0f);
    std::shared_ptr<ParticleDrag> drag = std::make_shared<ParticleDrag>(0.47f, 0.0f);

    p1->set_position(math::Vector3D(5.0f, 5.0f, 0.0f));

    this->force_registry.add_entry(p1, spring);
    this->force_registry.add_entry(p1, drag);
    this->force_registry.add_entry(p2, drag);

    this->particles.push_back(p1);
    this->particles.push_back(p2);
}

void PhysicWorld::update() {
    this->force_registry.update();

    for (auto particle : this->particles) {
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
