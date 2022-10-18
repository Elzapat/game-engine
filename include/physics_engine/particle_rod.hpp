#ifndef PARTICLE_ROD_HPP
#define PARTICLE_ROD_HPP

#include "particle_link.hpp"

class ParticleRod : ParticleLink {
    private:
        float lenght;

    public:
        ParticleRod();
        ~ParticleRod();
        
        void add_contact(ParticleContact* contact, unsigned int limit);
};

#endif