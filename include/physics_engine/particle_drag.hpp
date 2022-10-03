#ifndef PARTICLE_DRAG
#define PARTICLE_DRAG

#include "particle_force_generator.hpp"

class ParticleDrag : ParticleForceGenerator {
    private:
        float k1;
        float k2;
    
    public:
        void UpdateForce(Particle* particle, float duration);
};

#endif