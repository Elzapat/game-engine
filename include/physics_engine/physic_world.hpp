#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include <vector>
#include <memory>
#if defined(_MSC_VER)
    #include <corecrt_math_defines.h>
#endif

#include "vulkan_renderer/ui.hpp"

#include "particle.hpp"
#include "rigid_body.hpp"
#include "forces/particles/particle_force_registry.hpp"
#include "forces/particles/particle_spring.hpp"
#include "forces/particles/particle_anchored_spring.hpp"
#include "forces/particles/particle_drag.hpp"
#include "contacts/particles/particle_contact_generator.hpp"
#include "contacts/particles/particle_contact_resolver.hpp"
#include "contacts/particles/naive_particle_contact_generator.hpp"

class PhysicWorld {
    public:
        PhysicWorld();

        void update();

        void add_particle(const Particle particle);
        void add_particle(std::shared_ptr<Particle> particle);

        std::vector<std::shared_ptr<Particle>> get_particles() const;
        std::vector<std::shared_ptr<Particle>>& get_particles_ref();

    private:
        std::vector<std::shared_ptr<Particle>> particles;
        std::vector<std::unique_ptr<ParticleContactGenerator>> contact_generators;

        std::shared_ptr<ParticleAnchoredSpring> anchored_spring;

        ParticleForceRegistry force_registry;
        ParticleContactResolver contact_resolver;
};

#endif // PHYSIC_WORLD_HPP
