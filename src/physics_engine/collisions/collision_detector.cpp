#include "physics_engine/collisions/collision_detector.hpp"

void CollisionDetector::check_collision(
    std::shared_ptr<Primitive> _first,
    std::shared_ptr<Primitive> _second,
    CollisionData& data
) {
    if (auto first = std::dynamic_pointer_cast<Sphere>(_first)) {
        if (auto second = std::dynamic_pointer_cast<Sphere>(_second)) {
            this->sphere_sphere(*first.get(), *second.get(), data);
        } else if (auto second = std::dynamic_pointer_cast<Box>(_second)) {
            this->box_sphere(*second.get(), *first.get(), data);
        } else if (auto second = std::dynamic_pointer_cast<Plane>(_second)) {
            this->sphere_half_space(*first.get(), *second.get(), data);
        }
    } else if (auto first = std::dynamic_pointer_cast<Box>(_first)) {
        if (auto second = std::dynamic_pointer_cast<Sphere>(_second)) {
            this->box_sphere(*first.get(), *second.get(), data);
        } else if (auto second = std::dynamic_pointer_cast<Box>(_second)) {
            this->box_box(*second.get(), *first.get(), data);
        } else if (auto second = std::dynamic_pointer_cast<Plane>(_second)) {
            this->box_half_space(*first.get(), *second.get(), data);
        }
    } else if (auto first = std::dynamic_pointer_cast<Plane>(_first)) {
        if (auto second = std::dynamic_pointer_cast<Sphere>(_second)) {
            this->sphere_half_space(*second.get(), *first.get(), data);
        } else if (auto second = std::dynamic_pointer_cast<Box>(_second)) {
            this->box_half_space(*second.get(), *first.get(), data);
        }
    }
}

inline float CollisionDetector::projection_on_axis(const Box& box, const math::Vector3& axis) {
    return box.half_size.get_x() * std::abs(axis.dot(box.get_axis(0)))
        + box.half_size.get_y() * std::abs(axis.dot(box.get_axis(1)))
        + box.half_size.get_z() * std::abs(axis.dot(box.get_axis(2)));
}

inline float CollisionDetector::penetration_on_axis(
    const Box& box1,
    const Box& box2,
    const math::Vector3& axis,
    const math::Vector3& to_center
) {
    float projection1 = CollisionDetector::projection_on_axis(box1, axis);
    float projection2 = CollisionDetector::projection_on_axis(box2, axis);

    float distance = std::abs(to_center.dot(axis));

    return projection1 + projection2 - distance;
}

inline bool CollisionDetector::try_axis(
    const Box& one,
    const Box& two,
    math::Vector3 axis,
    const math::Vector3 to_center,
    unsigned index,
    float& smallestPen,
    unsigned& smallestCase
) {
    if (std::pow(axis.norm(), 2) < 0.0001) {
        return true;
    }

    axis = axis.normalize();

    float penetration = CollisionDetector::penetration_on_axis(one, two, axis, to_center);

    if (penetration < 0) {
        return false;
    }

    if (penetration < smallestPen) {
        smallestPen = penetration;
        smallestCase = index;
    }

    return true;
}

void CollisionDetector::fill_point_face_box_box(
    const Box& first,
    const Box& second,
    const math::Vector3 to_center,
    CollisionData& data,
    unsigned best,
    float pen
) {
    Contact contact(first.rigid_body, second.rigid_body, data.friction, data.restitution);

    math::Vector3 normal = first.get_axis(best);
    if (normal.dot(to_center) > 0) {
        normal *= -1.0f;
    }

    math::Vector3 vertex = second.half_size;

    if (second.get_axis(0).dot(normal) < 0) {
        vertex.set_x(-vertex.get_x());
    }

    if (second.get_axis(1).dot(normal) < 0) {
        vertex.set_y(-vertex.get_y());
    }

    if (second.get_axis(2).dot(normal) < 0) {
        vertex.set_z(-vertex.get_z());
    }

    contact.contact_normal = normal;
    contact.penetration = pen;
    contact.contact_point = second.get_transform() * vertex;
}

inline math::Vector3 CollisionDetector::contact_point(
    const math::Vector3& first_point,
    const math::Vector3 first_dir,
    float first_size,
    const math::Vector3& second_point,
    const math::Vector3& second_dir,
    float second_size,
    bool use_first
) {
    // dp = Dot Product, SM = Square Magnitude
    math::Vector3 to_st, c_first, c_second;
    float dp_sta_first, dp_sta_second, dp_first_second, sm_first, sm_second;
    float denom, mua, mub;

    sm_first = std::pow(first_dir.norm(), 2);
    sm_second = std::pow(second_dir.norm(), 2);
    dp_first_second = second_dir.dot(first_dir);

    to_st = first_point - second_point;
    dp_sta_first = first_dir.dot(to_st);
    dp_sta_second = second_dir.dot(to_st);

    denom = sm_first * sm_second - dp_first_second * dp_first_second;

    if (std::abs(denom) < 0.0001f) {
        return use_first ? first_point : second_point;
    }

    mua = (dp_first_second * dp_sta_second - sm_second * dp_sta_first) / denom;
    mub = (sm_first * dp_sta_second - dp_first_second * dp_sta_first) / denom;

    if (mua > first_size || mua < -first_size || mub > second_size || mub < -second_size) {
        return use_first ? first_point : second_point;
    } else {
        c_first = first_point + first_dir * mua;
        c_second = second_point + second_dir * mub;

        return c_first * 0.5f + c_second * 0.5f;
    }
}

void CollisionDetector::sphere_sphere(
    const Sphere& first,
    const Sphere& second,
    CollisionData& data
) {
    math::Vector3 first_pos = first.get_axis(3);
    math::Vector3 second_pos = second.get_axis(3);

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
    math::Vector3 sphere_pos = sphere.get_axis(3);
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
    math::Vector3 sphere_pos = sphere.get_axis(3);
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
        vertex_pos = vertex_pos.transform(box.get_transform());

        float vertex_distance = vertex_pos.dot(plane.normal);

        if (vertex_distance > plane.offset) {
            continue;
        }

        Contact contact(box.rigid_body, plane.rigid_body, data.friction, data.restitution);
        contact.contact_point = plane.normal * (vertex_distance - plane.offset) + vertex_pos;
        contact.contact_normal = plane.normal * 1.0f;
        contact.penetration = plane.offset - vertex_distance;

        std::cout << "contact point:" << contact.contact_point << std::endl;
        std::cout << "contact normal:" << contact.contact_normal << std::endl;
        data.contacts.push_back(contact);
    }
}

void CollisionDetector::box_sphere(const Box& box, const Sphere& sphere, CollisionData& data) {
    math::Vector3 sphere_center = sphere.get_axis(3);
    // Sphere center in box space coordinates
    sphere_center = sphere_center.transform(box.get_transform().inverse());

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
    closest_point = closest_point.transform(box.get_transform());

    Contact contact(box.rigid_body, sphere.rigid_body, data.friction, data.restitution);
    contact.contact_normal = (closest_point - sphere_center).normalize();
    contact.contact_point = closest_point;
    contact.penetration = sphere.radius - (closest_point - sphere_center).norm();

    data.contacts.push_back(contact);
}

#define CHECK_OVERLAP(axis, index) \
    if (!try_axis(first, second, (axis), to_center, (index), pen, best)) { \
        return; \
    }

void CollisionDetector::box_box(const Box& first, const Box& second, CollisionData& data) {
    math::Vector3 to_center = second.get_axis(3) - first.get_axis(3);

    float pen = std::numeric_limits<float>().max();
    unsigned best = std::numeric_limits<unsigned>().max();

    CHECK_OVERLAP(first.get_axis(0), 0);
    CHECK_OVERLAP(first.get_axis(1), 1);
    CHECK_OVERLAP(first.get_axis(2), 2);
    CHECK_OVERLAP(second.get_axis(3), 3);
    CHECK_OVERLAP(second.get_axis(4), 4);
    CHECK_OVERLAP(second.get_axis(5), 5);

    unsigned best_single_axis = best;

    CHECK_OVERLAP(first.get_axis(0).cross(second.get_axis(0)), 6);
    CHECK_OVERLAP(first.get_axis(0).cross(second.get_axis(1)), 7);
    CHECK_OVERLAP(first.get_axis(0).cross(second.get_axis(2)), 8);
    CHECK_OVERLAP(first.get_axis(1).cross(second.get_axis(0)), 9);
    CHECK_OVERLAP(first.get_axis(1).cross(second.get_axis(1)), 10);
    CHECK_OVERLAP(first.get_axis(1).cross(second.get_axis(2)), 11);
    CHECK_OVERLAP(first.get_axis(2).cross(second.get_axis(0)), 12);
    CHECK_OVERLAP(first.get_axis(2).cross(second.get_axis(1)), 13);
    CHECK_OVERLAP(first.get_axis(2).cross(second.get_axis(2)), 14);

    if (best == std::numeric_limits<unsigned>().max()) {
        std::cerr << "No best axis result" << std::endl;
        return;
        // throw std::runtime_error("No best axis result");
    }

    if (best < 3) {
        fill_point_face_box_box(first, second, to_center, data, best, pen);
    } else if (best < 6) {
        fill_point_face_box_box(second, first, to_center * -1.0f, data, best - 3, pen);
    } else {
        best -= 6;
        unsigned first_axis_index = best / 3;
        unsigned second_axis_index = best % 3;
        math::Vector3 first_axis = first.get_axis(first_axis_index);
        math::Vector3 second_axis = second.get_axis(second_axis_index);
        math::Vector3 axis = first_axis.cross(second_axis).normalize();

        if (axis.dot(to_center) > 0) {
            axis *= -1.0f;
        }

        math::Vector3 first_point = first.half_size;
        math::Vector3 second_point = second.half_size;

        for (unsigned i = 0; i < 3; i++) {
            if (i == first_axis_index) {
                first_point.values()[i] = 0;
            } else if (first.get_axis(i).dot(axis) > 0) {
                first_point.values()[i] *= -1.0f;
            }

            if (i == second_axis_index) {
                second_point.values()[i] = 0;
            } else if (second.get_axis(i).dot(axis) > 0) {
                second_point.values()[i] *= -1.0f;
            }
        }

        first_point = first.get_transform() * first_point;
        second_point = second.get_transform() * second_point;

        math::Vector3 vertex = CollisionDetector::contact_point(
            first_point,
            first_axis,
            first.half_size.values()[first_axis_index],
            second_point,
            second_axis,
            second.half_size.values()[second_axis_index],
            best_single_axis > 2
        );

        Contact contact(first.rigid_body, second.rigid_body, data.friction, data.restitution);
        contact.penetration = pen;
        contact.contact_normal = axis;
        contact.contact_point = vertex;
    }
}
