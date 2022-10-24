#ifndef PARTICLE_LINK_HPP
#define PARTICLE_LINK_HPP

#include "particle_contact_generator.hpp"

#include <vector>
#include <memory>

class ParticleLink : ParticleContactGenerator {
    protected:
        std::shared_ptr<Particle> particle1;
        std::shared_ptr<Particle> particle2;

    public:
        ParticleLink(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
        virtual ~ParticleLink();
        
        virtual void add_contact(std::vector<ParticleContact>& contacts);
        float current_length();
};

#endif
