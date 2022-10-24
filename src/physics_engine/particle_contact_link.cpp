#include "../../include/physics_engine/particle_link.hpp"

float ParticleLink::currentLenght(){

    math::Vector3D vector_distance = this->particles[0]->get_position - this->particles[1]->get_position;
    return vector_distance.norm;
}