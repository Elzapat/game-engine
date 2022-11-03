#ifndef NAIVE_PARTICLE_CONTACT_GENERATOR_HPP
#define NAIVE_PARTICLE_CONTACT_GENERATOR_HPP

#include "particle_contact_generator.hpp"

#include <vector>
#include <memory>

class NaiveParticleContactGenerator : public ParticleContactGenerator {
    public:
        float radius;
        std::vector<std::shared_ptr<Particle>> particles;

        NaiveParticleContactGenerator(std::vector<std::shared_ptr<Particle>> _particles, float _radius);

        void add_contact(std::vector<ParticleContact>& contacts) const;
};

#endif // NAIVE_PARTICLE_CONTACT_GENERATOR_HPP
