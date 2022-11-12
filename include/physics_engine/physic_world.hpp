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
#include "forces/rigid_bodies/force_generator.hpp"
#include "forces/rigid_bodies/force_registry.hpp"

class PhysicWorld {
    public:
        ParticleForceRegistry particle_force_registry;
        ForceRegistry force_registry;
        PhysicWorld();

        void update();

        void add_particle(const Particle particle);
        void add_particle(std::shared_ptr<Particle> particle);

        void add_rigid_body(const RigidBody rb);
        void add_rigid_body(std::shared_ptr<RigidBody> rb);

        std::vector<std::shared_ptr<Particle>> get_particles() const;
        std::vector<std::shared_ptr<Particle>>& get_particles_ref();

        std::vector<std::shared_ptr<RigidBody>> get_rigid_bodies() const;
        std::vector<std::shared_ptr<RigidBody>>& get_rigid_bodies_ref();

    private:
        std::vector<std::shared_ptr<Particle>> particles;
        std::vector<std::shared_ptr<RigidBody>> rigid_bodies;

        std::vector<std::unique_ptr<ParticleContactGenerator>> particle_contact_generators;
        ParticleContactResolver particle_contact_resolver;

};

#endif // PHYSIC_WORLD_HPP
