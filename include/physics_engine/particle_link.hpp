#ifndef PARTICLE_LINK_HPP
#define PARTICLE_LINK_HPP

#include "particle_contact_generator.hpp"

class ParticleLink : ParticleContactGenerator {
    private:
        Particle* particles[2]

    public:
        ParticleLink();
        ~ParticleLink();
        
        void add_contact(ParticleContact* contact, unsigned int limit);
        float currentLenght();
};

#endif