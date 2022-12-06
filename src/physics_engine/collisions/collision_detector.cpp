#include "physics_engine/collisions/collision_detector.hpp"

void CollisionDetector::sphere_sphere(
    const Sphere& first,
    const Sphere& second,
    CollisionData& data
) {
    math::Vector3 first_pos = first.rigid_body->get_position();
    math::Vector3 second_pos = second.rigid_body->get_position();

    math::Vector3 pos_diff = first_pos - second_pos;
    float size = pos_diff.norm();

    if (size <= 0.0f || size >= first.radius + second.radius) {
        return;
    }
    math::Vector3 normal = pos_diff * (1.0f / size);

    Contact contact(first.rigid_body, second.rigid_body, data.friction, data.restitution);
    contact.contact_point = first_pos + pos_diff * 0.5f;
    contact.contact_normal = normal;
    contact.penetration = first.radius + second.radius - size;

    data.contacts.push_back(contact);
    return;
}

void CollisionDetector::sphere_half_space(
    const Sphere& sphere,
    const Plane& plane,
    CollisionData& data
) {
    math::Vector3 sphere_pos = sphere.rigid_body->get_position();
    float sphere_distance = plane.normal.dot(sphere_pos) - sphere.radius - plane.offset;

    if (sphere_distance >= 0) {
        return;
    }

    Contact contact(sphere.rigid_body, plane.rigid_body, data.friction, data.restitution);
    contact.contact_normal = plane.normal;
    contact.penetration = -sphere_distance;
    contact.contact_point = sphere_pos - plane.normal * (sphere_distance + sphere.radius);

    data.contacts.push_back(contact);
    return;
}
