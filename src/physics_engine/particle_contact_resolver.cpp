#include "../../include/physics_engine/particle_contact_resolver.hpp"

ParticleContactResolver::ParticleContactResolver(unsigned int _iteration) : _iteration(_iteration) {}

ParticleContactResolver::ParticleContactResolver() {}

void ParticleContactResolver::resolve_contact(ParticleContact* contact_array, unsigned int num_contact, float duration) {
    for(int i = 0; i < num_contact; i++) {
        float velo_max = 0;
        float velo_tempo = 0;

        int num_velo_max = 0;

        for(int i = 0; i < num_contact; i++) {
            velo_tempo =  contact_array[num_contact].calculateSeparatingVelocity();
            if(velo_tempo > velo_max) {
                velo_max = velo_tempo;
                num_velo_max = num_contact;
            }
                

        }
    }
}