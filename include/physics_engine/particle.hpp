#ifndef PARTICULE_HPP
#define PARTICULE_HPP
// clang-format off
#include "../math/vector3D.hpp"

/*
* Class representing physical particule
*/
class Particule {
    private:
        math::Vector3D position, velocity, acceleration;
        float inv_mass, damping;

    public:
        Particule();
        Particule(
            math::Vector3D pos,
            math::Vector3D vel,
            math::Vector3D accel,
            float _inv_mass,
            float _damping
        );
        ~Particule();

        void set_position(math::Vector3D const& position);
        void set_velocity(math::Vector3D const& velocity);
        void set_acceleration(math::Vector3D const& acceleration);
        void set_inv_mass(float const& inv_mass);
        void set_damping(float const& damping);

        math::Vector3D get_position() const;
        math::Vector3D get_velocity() const;
        math::Vector3D get_acceleration() const;
        float get_inv_mass() const;
        float get_damping() const;

        void integrate(float dt);
};

#endif // PARTICULE_HPP
