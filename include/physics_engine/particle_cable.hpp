#ifndef PARTICLE_CABLE_HPP
#define PARTICLE_CABLE_HPP

#include "particle_link.hpp"

class ParticleCable : ParticleLink {
    private:
        float max_lenght;
        float restitution;
        
    public:
        ParticleCable();
        ~ParticleCable();
        
        void add_contact(ParticleContact* contact, unsigned int limit);
};

#endif