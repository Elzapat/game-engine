#ifndef PARTICLE_CONTACT_GENERATOR_HPP
#define PARTICLE_CONTACT_GENERATOR_HPP

#include "particle_contact.hpp"

#include <vector>
#include <memory>

class ParticleContactGenerator {
    private:

    public:
        ParticleContactGenerator();
        ~ParticleContactGenerator();

        virtual unsigned int add_contact(std::shared_ptr<ParticleContact> contact, unsigned int limit) const = 0;
};

#endif
