#include "../../include/physics_engine/particle_buoyancy.hpp"

ParticleBuoyancy :: ParticleBuoyancy(
    float _max_depth,
    float _volume,
    float _water_height,
    float _liquid_density
) : 
    max_depth(_max_depth),
    volume(_volume),
    water_height(_water_height),
    liquid_density(_liquid_density) {}

ParticleBuoyancy :: ~ParticleBuoyancy() {}

void ParticleBuoyancy::update_force(Particle* particle, float duration) {

    float d = ( particle->get_position().get_y() - water_height - max_depth ) / ( 2 * max_depth );

    math::Vector3D force_to_add(0, d * liquid_density, 0);

    math::Vector3D new_acceleration = particle->get_acceleration() + force_to_add;

    particle->set_acceleration(new_acceleration);
}