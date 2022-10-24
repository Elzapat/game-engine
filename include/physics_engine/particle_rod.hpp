#ifndef PARTICLE_ROD_HPP
#define PARTICLE_ROD_HPP

#include "particle_link.hpp"

class ParticleRod : ParticleLink {
    private:
        float lenght;

    public:
        ParticleRod(
            Particle* particle_1,
            Particle* particle_2,
            float lenght);
        ~ParticleRod();
        
        void add_contact(std::vector<ParticleContact>& contacts);
};

#endif