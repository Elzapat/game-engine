#ifndef PARTICLE_SPRING_HPP
#define PARTICLE_SPRING_HPP

#include "particle_force_generator.hpp"

class ParticleSpring : ParticleForceGenerator {
    private:
        Particle* other;
        float k;
        float rest_length;

    public:
        ParticleSpring(
            Particle* _other,
            float _k,
            float _rest_length
        );
        ~ParticleSpring();

        void update_force(Particle* particle, float duration);
};

#endif