#include "physics_engine/collisions/collision_detector.hpp"

inline math::Vector3
CollisionDetector::projection_on_axis(const math::Vector3& vector, const math::Vector3& axis) {
    float dot = vector.dot(axis);
    return math::Vector3(dot * axis.get_x(), dot * axis.get_y(), dot * axis.get_y());
}

inline float CollisionDetector::penetration_on_axis(
    const Box& box1,
    const Box& box2,
    const math::Vector3& axis,
    const math::Vector3& to_center
) {
    float projection1 = CollisionDetector::projection_on_axis(box1.half_size, axis).norm();
    float projection2 = CollisionDetector::projection_on_axis(box2.half_size, axis).norm();

    float distance = std::abs(to_center.dot(axis));

    return projection1 + projection2 - distance;
}

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
}

void CollisionDetector::sphere_plane(
    const Sphere& sphere,
    const Plane& plane,
    CollisionData& data
) {
    math::Vector3 sphere_pos = sphere.rigid_body->get_position();
    float sphere_distance = plane.normal.dot(sphere_pos) - plane.offset;

    if (sphere_distance * sphere_distance > sphere.radius * sphere.radius) {
        return;
    }

    math::Vector3 normal = plane.normal;
    float penetration = -sphere_distance;

    if (sphere_distance < 0) {
        normal *= -1.0f;
        penetration *= -1.0f;
    }

    Contact contact(sphere.rigid_body, plane.rigid_body, data.friction, data.restitution);
    contact.contact_normal = normal;
    contact.penetration = penetration;
    contact.contact_point = sphere_pos - plane.normal * sphere_distance;

    data.contacts.push_back(contact);
}

void CollisionDetector::box_half_space(const Box& box, const Plane& plane, CollisionData& data) {
    constexpr std::array<std::array<float, 3>, 8> mults = {{
        {1, 1, 1},
        {-1, 1, 1},
        {1, -1, 1},
        {-1, -1, 1},
        {1, 1, -1},
        {-1, 1, -1},
        {1, -1, -1},
        {-1, -1, -1}  //
    }};

    for (std::size_t i = 0; i < mults.size(); i++) {
        math::Vector3 vertex_pos = math::Vector3(
            mults[i][0] * box.half_size.get_x(),
            mults[i][1] * box.half_size.get_y(),
            mults[i][2] * box.half_size.get_z()
        );
        vertex_pos = vertex_pos.transform(box.rigid_body->get_transform());

        float vertex_distance = vertex_pos.dot(plane.normal);

        if (vertex_distance > plane.offset) {
            continue;
        }

        Contact contact(box.rigid_body, plane.rigid_body, data.friction, data.restitution);
        contact.contact_point = plane.normal * (vertex_distance - plane.offset) + vertex_pos;
        contact.contact_normal = plane.normal;
        contact.penetration = plane.offset - vertex_distance;

        data.contacts.push_back(contact);
    }
}

void CollisionDetector::box_sphere(const Box& box, const Sphere& sphere, CollisionData& data) {
    math::Vector3 sphere_center = sphere.rigid_body->get_position();
    // Sphere center in box space coordinates
    sphere_center = sphere_center.transform(box.rigid_body->get_transform().inverse());

    if (std::abs(sphere_center.get_x()) - sphere.radius > box.half_size.get_x()
        || std::abs(sphere_center.get_y()) - sphere.radius > box.half_size.get_y()
        || std::abs(sphere_center.get_z()) - sphere.radius > box.half_size.get_z())  //
    {
        return;
    }

    math::Vector3 closest_point(
        std::clamp(sphere_center.get_x(), -box.half_size.get_x(), box.half_size.get_x()),
        std::clamp(sphere_center.get_y(), -box.half_size.get_y(), box.half_size.get_y()),
        std::clamp(sphere_center.get_z(), -box.half_size.get_z(), box.half_size.get_z())
    );

    if (std::pow((closest_point - sphere_center).norm(), 2) > std::pow(sphere.radius, 2)) {
        return;
    }

    // Sphere center in world coordinates
    closest_point = closest_point.transform(box.rigid_body->get_transform());

    Contact contact(box.rigid_body, sphere.rigid_body, data.friction, data.restitution);
    contact.contact_normal = (closest_point - sphere_center).normalize();
    contact.contact_point = closest_point;
    contact.penetration = sphere.radius - (closest_point - sphere_center).norm();

    data.contacts.push_back(contact);
}
