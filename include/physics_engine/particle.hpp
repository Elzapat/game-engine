#ifndef PARTICULE_HPP
#define PARTICULE_HPP

// clang-format off
#include "../math/vector3.hpp"
#include "../time.hpp"

/*
* Class representing physical particule
*/
class Particle {
    private:
        math::Vector3 position, velocity, acceleration;
        math::Vector3 forces;
        float inv_mass;

    public:
        Particle();
        Particle(
            math::Vector3 pos,
            math::Vector3 vel,
            math::Vector3 accel,
            float _inv_mass
        );
        ~Particle();

        void set_position(const math::Vector3 position);
        void set_velocity(const math::Vector3 velocity);
        void set_acceleration(const math::Vector3 acceleration);
        void set_inv_mass(const float inv_mass);
        void set_mass(const float mass);
        void set_forces(math::Vector3 forces);

        math::Vector3 get_position() const;
        math::Vector3 get_velocity() const;
        math::Vector3 get_acceleration() const;
        float get_inv_mass() const;
        float get_mass() const;
        math::Vector3 get_forces() const;

        void add_force(math::Vector3 force);
        void apply_impulse(math::Vector3 impulse);

        void integrate();
};

#endif // PARTICULE_HPP
