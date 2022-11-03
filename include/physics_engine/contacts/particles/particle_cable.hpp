#ifndef PARTICLE_CABLE_HPP
#define PARTICLE_CABLE_HPP

#include "particle_link.hpp"

#include <vector>
#include <memory>

class ParticleCable : public ParticleLink {
    private:
        float max_length;
        float restitution;
        
    public:
        ParticleCable(
            std::shared_ptr<Particle> p1,
            std::shared_ptr<Particle> p2,
            float _max_length,
            float _restitution
        );
        ~ParticleCable();
        
        void add_contact(std::vector<ParticleContact>& contacts);
};

#endif
