#ifndef PARTICLE_CONTACT_RESOLVER_HPP
#define PARTICLE_CONTACT_RESOLVER_HPP

#include "particle_contact.hpp"

#include <vector>
#include <limits>
#include <algorithm>

class ParticleContactResolver {
    private:
        uint32_t max_iterations;

    public:
        ParticleContactResolver(unsigned int _max_iterations = 50);
        ~ParticleContactResolver();
        
        void resolve_contacts(std::vector<ParticleContact> contacts);
        
};

#endif
