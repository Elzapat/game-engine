#ifndef PARTICLE_LINK_HPP
#define PARTICLE_LINK_HPP

#include "particle_contact_generator.hpp"

class ParticleLink : ParticleContactGenerator {
    protected:
        Particle* particles[2]

    public:
        ParticleLink();
        ~ParticleLink();
        
        virtual void add_contact(std::vector<ParticleContact>& contacts);
        float currentLenght();
};

#endif