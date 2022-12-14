#ifndef PARTICLE_CONTACT_HPP
#define PARTICLE_CONTACT_HPP

#include "physics_engine/particle.hpp"
#include "math/vector3.hpp"

#include <memory>

class ParticleContact {
    public:
        std::shared_ptr<Particle> particle1;
        std::shared_ptr<Particle> particle2;
        float restitution;
        float penetration;
        math::Vector3 normal;

        ParticleContact(
            std::shared_ptr<Particle> p1,
            std::shared_ptr<Particle> p2,
            float _restitution,
            float _penetration
        );
        ~ParticleContact();
        
        void resolve();
        math::Vector3 relative_velocity();
        float separating_velocity();

    private:
        void resolve_velocity();
        void resolve_interpenetration();
};

#endif
