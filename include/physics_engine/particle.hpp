#ifndef PARTICULE_HPP
#define PARTICULE_HPP

// clang-format off
#include "../math/vector3D.hpp"
#include "../time.hpp"

/*
* Class representing physical particule
*/
class Particle {
    private:
        math::Vector3D position, velocity, acceleration;
        math::Vector3D forces;
        float inv_mass;

    public:
        Particle();
        Particle(
            math::Vector3D pos,
            math::Vector3D vel,
            math::Vector3D accel,
            float _inv_mass
        );
        ~Particle();

        void set_position(const math::Vector3D position);
        void set_velocity(const math::Vector3D velocity);
        void add_velocity(math::Vector3D delta_vel);
        void set_acceleration(const math::Vector3D acceleration);
        void set_inv_mass(const float inv_mass);
        void set_mass(const float mass);
        void set_forces(math::Vector3D forces);

        math::Vector3D get_position() const;
        math::Vector3D get_velocity() const;
        math::Vector3D get_acceleration() const;
        float get_inv_mass() const;
        float get_mass() const;
        math::Vector3D get_forces() const;

        void add_force(math::Vector3D force);

        void integrate();
};

#endif // PARTICULE_HPP
