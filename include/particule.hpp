#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "vector3D.hpp"

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

        Vector3D get_position();
        Vector3D get_velocity();
        Vector3D get_acceleration();
        float get_inv_mass();
        float get_damping();

        void integrate(int time_delta);

};

#endif // PARTICULE_HPP
