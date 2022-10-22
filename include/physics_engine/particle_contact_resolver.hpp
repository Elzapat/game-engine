#ifndef PARTICLE_CONTACT_RESOLVER_HPP
#define PARTICLE_CONTACT_RESOLVER_HPP

#include "particle_contact.hpp"

class ParticleContactResolver {
    private:
        unsigned int iteration;

    public:
        ParticleContactResolver(unsigned int _iteration);
        ~ParticleContactResolver();
        
        void resolve_contact(ParticleContact* contact_array, unsigned int num_contact, float duration);
        
};

#endif