#include "physics_engine/collisions/bounding_sphere.hpp"

BoundingSphere::BoundingSphere(math::Vector3 _center, float _radius) :
    center(_center),
    radius(_radius) {}

BoundingSphere::BoundingSphere(BoundingSphere first, BoundingSphere second) {
    math::Vector3 center_offset = second.center - first.center;
    float distance = std::pow(center_offset.norm(), 2);
    float radius_diff = second.radius - first.radius;

    if (radius_diff * radius_diff >= distance) {
        if (first.radius > second.radius) {
            this->center = first.center;
            this->radius = first.radius;
        } else {
            this->center = second.center;
            this->radius = second.radius;
        }
    } else {
        distance = std::sqrt(distance);
        this->radius = (distance + first.radius + second.radius) * 0.5f;

        this->center = first.center;
        if (distance > 0.0f) {
            this->center += center_offset * ((this->radius - first.radius) / distance);
        }
    }
}

bool BoundingSphere::overlaps(const BoundingSphere& other) const {
    float distance_squared = std::pow((this->center - other.center).norm(), 2);
    return distance_squared < (this->radius + other.radius) * (this->radius + other.radius);
}
