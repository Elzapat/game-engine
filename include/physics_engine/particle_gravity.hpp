#ifndef PARTICLE_GRAVITY_HPP
#define PARTICLE_GRAVITY_HPP

#include "particle_force_generator.hpp"

class ParticleGravity : ParticleForceGenerator {
    private:
        math::Vector3D gravity;

    public:
        ParticleGravity(math::Vector3D _gravity);

        void UpdateForce(Particle* particle, float duration);
};

#endif