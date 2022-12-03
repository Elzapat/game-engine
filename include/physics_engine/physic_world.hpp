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
#include "object.hpp"
#include "forces/particles/particle_force_registry.hpp"
#include "forces/particles/particle_spring.hpp"
#include "forces/particles/particle_anchored_spring.hpp"
#include "forces/particles/particle_drag.hpp"
#include "contacts/particles/particle_contact_generator.hpp"
#include "contacts/particles/particle_contact_resolver.hpp"
#include "contacts/particles/naive_particle_contact_generator.hpp"
#include "forces/rigid_bodies/force_generator.hpp"
#include "forces/rigid_bodies/force_registry.hpp"

class PhysicWorld {
    public:
        ParticleForceRegistry particle_force_registry;
        ForceRegistry force_registry;
        PhysicWorld();

        void update(std::vector<Object>& objects);

    private:
        std::vector<std::shared_ptr<Particle>> particles;
        std::vector<std::shared_ptr<RigidBody>> rigid_bodies;

        std::vector<std::unique_ptr<ParticleContactGenerator>> particle_contact_generators;
        ParticleContactResolver particle_contact_resolver;

};

#endif // PHYSIC_WORLD_HPP
