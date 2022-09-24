#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include <vector>

#include "particule.hpp"

class PhysicWorld {
    public:
        void update(float dt);

    private:
        float gravity = 9.8f;
        std::vector<Particule> particules;
};

#endif // PHYSIC_WORLD_HPP
