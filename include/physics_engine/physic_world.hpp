#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include <vector>

#include "particule.hpp"

class PhysicWorld {
    public:
        void update(float dt);

        void add_particule(const Particule particule);

        std::vector<Particule> get_particules() const;
        std::vector<Particule>& get_particules_ref();

    private:
        std::vector<Particule> particules;
};

#endif // PHYSIC_WORLD_HPP
