#ifndef PARTICLE_GRAVITY_HPP
#define PARTICLE_GRAVITY_HPP

#include "particle_force_generator.hpp"
#include "../time.hpp"

class ParticleGravity : public ParticleForceGenerator {
    private:
        math::Vector3 gravity;

    public:
        ParticleGravity(math::Vector3 _gravity);
        ~ParticleGravity();

        void update_force(Particle* particle);
};

#endif
