#include "../../include/physics_engine/physic_world.hpp"

PhysicWorld::PhysicWorld() : contact_resolver() {
    // Forces
    auto drag = std::make_shared<ParticleDrag>(0.47f, 0.0f);
    this->anchored_spring = std::make_shared<ParticleAnchoredSpring>(math::Vector3D(), 50.0f, 1.0f);

    // Generate all particles
    const int SLICES = 11;
    const int STACKS = 10;
    /* const int SLICES = 3; */
    /* const int STACKS = 3; */

    const int RADIUS = 15;

    float sector_step = 2.0f * M_PI / static_cast<float>(SLICES);
    float stack_step = M_PI / static_cast<float>(STACKS);

    for (int i = 0; i <= SLICES; i++) {
        float stack_angle = M_PI / 2.0f - static_cast<float>(i) * stack_step;
        float xy = static_cast<float>(RADIUS) * std::cos(stack_angle);
        float z = static_cast<float>(RADIUS) * std::sin(stack_angle);

        for (int j = 0; j <= STACKS; j++) {
            float sector_angle = static_cast<float>(j) * sector_step;

            float x = xy * std::cos(sector_angle);
            float y = xy * std::sin(sector_angle);

            std::shared_ptr<Particle> particle = std::make_shared<Particle>();
            particle->set_position(math::Vector3D(x, y, z));

            this->force_registry.add_entry(particle, drag);
            this->force_registry.add_entry(particle, anchored_spring);

            if (this->particles.size() >= 1) {
                int random_idx = rand() % particles.size();
                std::shared_ptr<ParticleSpring> spring =
                    std::make_shared<ParticleSpring>(this->particles[random_idx], 5.0f, 10.0f);

                this->force_registry.add_entry(particle, spring);
            }

            this->particles.push_back(particle);
            particle->set_mass(50.0f);
        }
    }

    auto contact = std::make_unique<NaiveParticleContactGenerator>(this->particles, 1.0f);
    this->contact_generators.push_back(std::move(contact));
}

void PhysicWorld::update() {
    this->anchored_spring->anchor = Ui::spring_anchor;
    this->anchored_spring->rest_length = Ui::anchored_spring_rest_length;
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
