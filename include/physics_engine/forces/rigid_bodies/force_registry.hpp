#ifndef FORCE_REGISTRY_HPP
#define FORCE_REGISTRY_HPP

#include "physics_engine/rigid_body.hpp"
#include "force_generator.hpp"
#include "time.hpp"

#include <vector>
#include <algorithm>
#include <memory>

class ForceRegistry {
    private: 
        struct ForceEntry {
            std::shared_ptr<RigidBody> rigid_body;
            std::shared_ptr<ForceGenerator> force_generator;
        };
    
        std::vector<ForceEntry> registry;

    public: 
        ForceRegistry();
        ~ForceRegistry();

        void add_entry(std::shared_ptr<RigidBody> rigid_body, std::shared_ptr<ForceGenerator> force_generator);

        void update();
};

#endif // FORCE_REGISTRY_HPP
