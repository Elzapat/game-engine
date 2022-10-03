#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include <vector>

#include "particle.hpp"

class PhysicWorld {
    public:
        void update(float dt);

        void add_particle(const Particle particle);

        std::vector<Particle> get_particles() const;
        std::vector<Particle>& get_particles_ref();

    private:
        std::vector<Particle> particles;
};

#endif // PHYSIC_WORLD_HPP
