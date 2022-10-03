#ifndef PARTICLE_DRAG
#define PARTICLE_DRAG

#include "particle_force_generator.hpp"

class ParticleDrag : ParticleForceGenerator {
    private:
        float k1;
        float k2;
    
    public:
        ParticleDrag(float _k1, float _k2);
        ~ParticleDrag();
        void update_force(Particle* particle, float duration);
};

#endif