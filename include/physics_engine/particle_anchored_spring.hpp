#ifndef PARTICLE_ANCHORED_SPRING_HPP
#define PARTICLE_ANCHORED_SPRING_HPP

#include "particle_force_generator.hpp"

class ParticleAnchoredSpring : ParticleForceGenerator {
    private:
        math::Vector3D anchor;
        float k;
        float rest_length;

    public:
        ParticleAnchoredSpring(
            math::Vector3D _anchor,
            float _k,
            float _rest_length
        );
        ~ParticleAnchoredSpring();

        void update_force(Particle* particle, float duration);
};

#endif