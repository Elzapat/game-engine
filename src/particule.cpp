#include "../include/particule.hpp"

Particule::Particule() {}

void Particule::integrate(int time_delta) {

    this->position = (this->acceleration)*pow(time_delta,2)*0.5 + this->velocity*time_delta + this->position;
    this->velocity = (this->acceleration)*time_delta + this->velocity;

}