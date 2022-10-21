#ifndef PARTICLE_FORCE_REGISTRY_HPP
#define PARTICLE_FORCE_REGISTRY_HPP

#include "particle.hpp"
#include "particle_force_generator.hpp"
#include "../time.hpp"

#include <vector>
#include <algorithm>
#include <memory>

class ParticleForceRegistry {
    private: 
        struct ParticleForceEntry {
            std::shared_ptr<Particle> particle;
            std::shared_ptr<ParticleForceGenerator> force_generator;
        };
    
        using Registry = std::vector<ParticleForceEntry>;
        Registry registry;

    public: 
        ParticleForceRegistry();
        ~ParticleForceRegistry();

        void add_entry(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> force_generator);
        void remove_entry(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> force_generator);

        void update();
};

#endif
