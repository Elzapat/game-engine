#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP

#include <vector>

#include "physics_engine/contacts/rigid_bodies/contact.hpp"
#include "physics_engine/primitives/sphere.hpp"
#include "physics_engine/primitives/plane.hpp"

#include "math/vector3.hpp"

struct CollisionData {
    std::vector<Contact> contacts;
    float friction;
    float restitution;
};

class CollisionDetector {
    public:
        void sphere_sphere(const Sphere& first, const Sphere& second, CollisionData& data);
        void sphere_half_space(const Sphere& sphere, const Plane& plane, CollisionData& data);
};

#endif // COLLISION_DETECTOR_HPP
