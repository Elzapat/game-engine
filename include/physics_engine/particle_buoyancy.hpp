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
        ParticleBuoyancy(
            float _max_depth,
            float _volume,
            float _water_height,
            float _liquid_density
        );
        ~ParticleBuoyancy();
        
        void update_force(Particle* particle);
};

#endif
