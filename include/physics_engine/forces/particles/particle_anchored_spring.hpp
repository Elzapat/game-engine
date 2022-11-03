#ifndef PARTICLE_ANCHORED_SPRING_HPP
#define PARTICLE_ANCHORED_SPRING_HPP

#include "particle_force_generator.hpp"
#include "../../../time.hpp"

#include <memory>

class ParticleAnchoredSpring : public ParticleForceGenerator {
    public:
        math::Vector3 anchor;
        float k;
        float rest_length;

        ParticleAnchoredSpring(
            math::Vector3 _anchor,
            float _k,
            float _rest_length
        );
        ~ParticleAnchoredSpring();

        void update_force(std::shared_ptr<Particle>);
};

#endif
