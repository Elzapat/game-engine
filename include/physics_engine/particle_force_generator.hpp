#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "particle.hpp"

#include <memory>

class ParticleForceGenerator {
    public:
        virtual void update_force(std::shared_ptr<Particle> particule) = 0;
};

#endif
