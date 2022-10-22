#ifndef NAIVE_PARTICLE_CONTACT_GENERATOR_HPP
#define NAIVE_PARTICLE_CONTACT_GENERATOR_HPP

#include "particle_contact_generator.hpp"

#include <vector>
#include <memory>

class NaiveParticleContactGenerator : public ParticleContactGenerator {
    public:
        float radius;
        std::vector<std::shared_ptr<Particle>> particles;

        unsigned int add_contact(std::shared_ptr<ParticleContact>, unsigned int limit) const;
};

#endif // NAIVE_PARTICLE_CONTACT_GENERATOR_HPP
