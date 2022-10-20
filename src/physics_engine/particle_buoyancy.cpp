#include "../../include/physics_engine/particle_buoyancy.hpp"

ParticleBuoyancy ::ParticleBuoyancy(
    float _max_depth,
    float _volume,
    float _water_height,
    float _liquid_density
) :
    max_depth(_max_depth),
    volume(_volume),
    water_height(_water_height),
    liquid_density(_liquid_density) {}

ParticleBuoyancy ::~ParticleBuoyancy() {}

void ParticleBuoyancy::update_force(Particle* particle) {
    float y = particle->get_position().get_y();

    float d = (y - this->water_height - this->max_depth) / (2 * this->max_depth);
    math::Vector3D buoyancy(0, d * this->liquid_density, 0);

    particle->add_force(buoyancy * Time::delta_time());
}
