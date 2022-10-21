#ifndef PARTICLE_SPRING_HPP
#define PARTICLE_SPRING_HPP

#include "particle_force_generator.hpp"
#include "../time.hpp"

#include <memory>

class ParticleSpring : public ParticleForceGenerator {
    private:
        std::shared_ptr<Particle> other;
        float k;
        float rest_length;

    public:
        ParticleSpring(
            std::shared_ptr<Particle> _other,
            float _k,
            float _rest_length
        );
        ~ParticleSpring();

        void update_force(std::shared_ptr<Particle> particle);
};

#endif
