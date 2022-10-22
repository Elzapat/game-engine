#ifndef PARTICLE_CONTACT_GENERATOR_HPP
#define PARTICLE_CONTACT_GENERATOR_HPP

#include "particle_contact.hpp"

#include <vector>
#include <memory>

class ParticleContactGenerator {
    public:
        virtual void add_contact(std::vector<ParticleContact>& contacts) const = 0;
};

#endif
