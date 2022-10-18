#ifndef PARTICLE_CONTACT_GENERATOR_HPP
#define PARTICLE_CONTACT_GENERATOR_HPP

#include "particle_contact.hpp"

class ParticleContactGenerator {
    private:

    public:
        ParticleContactGenerator();
        ~ParticleContactGenerator();

        virtual void add_contact(ParticleContact* contact, unsigned int limit);
        
};

#endif