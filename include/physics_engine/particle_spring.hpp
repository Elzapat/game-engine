#ifndef PARTICLE_SPRING_HPP
#define PARTICLE_SPRING_HPP

#include "particle_force_generator.hpp"

class ParticleSpring : ParticleForceGenerator {
    private:
        Particle* other;
        float k;
        float rest_length;

    public:
        ParticleSpring(Particle* other, float k, float rest_length);
        
        void UpdateForce(Particle* particle, float duration);
};

#endif