#ifndef PARTICLE_ROD_HPP
#define PARTICLE_ROD_HPP

#include "particle_link.hpp"

#include <vector>
#include <memory>

class ParticleRod : public ParticleLink {
    private:
        float length;

    public:
        ParticleRod(
            std::shared_ptr<Particle> p1,
            std::shared_ptr<Particle> p2,
            float length
        );
        ~ParticleRod();
        
        void add_contact(std::vector<ParticleContact>& contacts);
};

#endif
