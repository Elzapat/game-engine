#ifndef PARTICLE_BUOYANCY_HPP
#define PARTICLE_BUOYANCY_HPP

#include "particle_force_generator.hpp"

class ParticleBuoyancy : ParticleForceGenerator {
    private:
    float max_depth;
    float volume;
    
    float water_height;
    float liquid_density;

    public:
        ParticleBuoyancy(float max_depth, float volume, float water_height, float liquid_density);
        
        void UpdateForce(Particle* particle, float duration);
};

#endif