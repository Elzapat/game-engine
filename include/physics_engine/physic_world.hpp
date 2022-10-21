#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include <vector>
#include <memory>

#include "particle.hpp"
#include "particle_force_registry.hpp"
#include "particle_spring.hpp"
#include "particle_drag.hpp"

class PhysicWorld {
    public:
        PhysicWorld();

        void update();

        void add_particle(const Particle particle);
        void add_particle(std::shared_ptr<Particle> particle);

        std::vector<std::shared_ptr<Particle>> get_particles() const;
        std::vector<std::shared_ptr<Particle>>& get_particles_ref();

    private:
        std::vector<std::shared_ptr<Particle>> particles;
        ParticleForceRegistry force_registry;
};

#endif // PHYSIC_WORLD_HPP
