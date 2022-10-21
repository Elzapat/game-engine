#ifndef PARTICLE_GRAVITY_HPP
#define PARTICLE_GRAVITY_HPP

#include "particle_force_generator.hpp"
#include "../time.hpp"

class ParticleGravity : public ParticleForceGenerator {
    private:
        math::Vector3D gravity;

    public:
        ParticleGravity(math::Vector3D _gravity);
        ~ParticleGravity();

        void update_force(Particle* particle);
};

#endif
