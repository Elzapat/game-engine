#ifndef PARTICLE_FORCE_REGISTRY_HPP
#define PARTICLE_FORCE_REGISTRY_HPP

#include "particle.hpp"
#include "particle_force_generator.hpp"
#include <vector>
#include <algorithm>

class ParticleForceRegistry {
    private: 
        struct ParticleForceEntry {
            Particle* particle;
            ParticleForceGenerator* force_generator;
        };
    
    using Registry = std::vector<ParticleForceEntry>;
    Registry registry;

    public: 
        ParticleForceRegistry();
        ~ParticleForceRegistry();

        void add_entry(Particle* particle, ParticleForceGenerator* force_generator);
        void remove_entry(Particle* particle, ParticleForceGenerator* force_generator);

        void update_force(float duration);
        
};

#endif