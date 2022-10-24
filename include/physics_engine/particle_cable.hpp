#ifndef PARTICLE_CABLE_HPP
#define PARTICLE_CABLE_HPP

#include "particle_link.hpp"

class ParticleCable : ParticleLink {
    private:
        float max_lenght;
        float restitution;
        
    public:
        ParticleCable(
            Particle* particle_1,
            Particle* particle_2,
            float max_lenght
            float restitution);
        ~ParticleCable();
        
        void add_contact(std::vector<ParticleContact>& contacts);
};

#endif