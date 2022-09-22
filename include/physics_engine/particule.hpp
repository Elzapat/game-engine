#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "../math/vector3D.hpp"

/*
* Class representing physical particule
*/
class Particule {
    private:
        Vector3D position, velocity, acceleration;
        float inv_mass, damping;

    public:
        Particule();
        ~Particule();

        void set_position(Vector3D const& position);
        void set_velocity(Vector3D const& velocity);
        void set_acceleration(Vector3D const& acceleration);
        void set_inv_mass(float const& inv_mass);
        void set_damping(float const& damping);

        Vector3D get_position() const;
        Vector3D get_velocity() const;
        Vector3D get_acceleration() const;
        float get_inv_mass() const;
        float get_damping() const;

        void integrate(float dt);
};

#endif // PARTICULE_HPP
