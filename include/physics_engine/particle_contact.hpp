#ifndef PARTICLE_CONTACT_HPP
#define PARTICLE_CONTACT_HPP

#include "particle.hpp"

class ParticleContact {
    private:
        Particle* particles[2];
        float restitution;
        float penetration;
        math::Vector3D contact_normal;

        void resolveVelocity(float duration);
        void resolveInterpenetration(float duration);

    public:
        ParticleContact(
            Particle* _particle,
            Particle* _other_particle,
            float _restitution,
            float _penetration);
        ~ParticleContact();
        
        void resolve(float duration);
        float calculateSeparatingVelocity();
        
};

#endif