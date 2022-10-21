#ifndef PARTICLE_DRAG
#define PARTICLE_DRAG

#include "particle_force_generator.hpp"
#include "../time.hpp"

#include <memory>

class ParticleDrag : public ParticleForceGenerator {
    private:
        float k1;
        float k2;
    
    public:
        ParticleDrag(float _k1 = 1, float _k2 = 1);
        ~ParticleDrag();
        void update_force(std::shared_ptr<Particle> particle);
};

#endif
