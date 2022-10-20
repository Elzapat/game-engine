#ifndef PARTICULE_HPP
#define PARTICULE_HPP
// clang-format off
#include "../math/vector3D.hpp"

/*
* Class representing physical particule
*/
class Particle {
    private:
        math::Vector3D position, velocity, acceleration;
        math::Vector3D forces;
        float inv_mass, damping;

    public:
        Particle();
        Particle(
            math::Vector3D pos,
            math::Vector3D vel,
            math::Vector3D accel,
            float _inv_mass,
            float _damping
        );
        ~Particle();

        void set_position(math::Vector3D const position);
        void set_velocity(math::Vector3D const velocity);
        void set_acceleration(math::Vector3D const acceleration);
        void set_inv_mass(float const inv_mass);
        void set_damping(float const damping);
        void set_forces(math::Vector3D forces);

        math::Vector3D get_position() const;
        math::Vector3D get_velocity() const;
        math::Vector3D get_acceleration() const;
        float get_inv_mass() const;
        float get_damping() const;
        math::Vector3D get_forces() const;

        void add_force(math::Vector3D force);

        void integrate(float dt);
};

#endif // PARTICULE_HPP
