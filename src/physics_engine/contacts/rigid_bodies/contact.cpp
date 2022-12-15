#include "physics_engine/contacts/rigid_bodies/contact.hpp"

Contact::Contact(
    std::shared_ptr<RigidBody> _first,
    std::shared_ptr<RigidBody> _second,
    float _friction,
    float _restitution
) :
    first(_first),
    second(_second),
    friction(_friction),
    restitution(_restitution) {}

void Contact::calculate_internals() {
    this->calculate_contact_basis();

    this->first_relative_contact_pos = this->contact_point - first->get_position();
    if (this->second != nullptr) {
        this->second_relative_contact_pos = this->contact_point - second->get_position();
    }

    this->contact_velocity = this->calculate_local_velocity(first, first_relative_contact_pos);
    if (this->second != nullptr) {
        this->calculate_local_velocity(second, second_relative_contact_pos);
    }

    this->calculate_desired_delta_velocity();
}

math::Vector3
Contact::calculate_local_velocity(std::shared_ptr<RigidBody> body, math::Vector3& rel_contact_pos) {
    math::Vector3 velocity = body->get_rotation().cross(rel_contact_pos) + body->get_velocity();

    math::Vector3 contact_velocity = velocity.transform(this->contact_to_world);
    math::Vector3 accel_velocity =
        (body->get_acceleration() * Time::delta_time()).transform(this->contact_to_world);

    accel_velocity.set_x(0.0f);
    contact_velocity += accel_velocity;

    return contact_velocity;
}

void Contact::calculate_desired_delta_velocity() {
    constexpr float vel_limit = 0.25f;

    float vel_from_acc = 0.0f;

    vel_from_acc += (first->get_acceleration() * Time::delta_time()).dot(this->contact_normal);
    vel_from_acc -= (second->get_acceleration() * Time::delta_time()).dot(this->contact_normal);

    float restitution = this->restitution;
    if (std::abs(this->contact_velocity.get_x()) < vel_limit) {
        restitution = 0.0f;
    }

    this->desired_delta_velocity = -this->contact_velocity.get_x()
        - restitution * (this->contact_velocity.get_x() - vel_from_acc);
}

void Contact::calculate_contact_basis() {
    std::array<math::Vector3, 2> contact_tangent;

    if (std::abs(this->contact_normal.get_x()) > std::abs(this->contact_normal.get_y())) {
        const float scale = 1.0f
            / std::sqrt(std::pow(this->contact_normal.get_z(), 2)
                        + std::pow(this->contact_normal.get_x(), 2));

        contact_tangent[0].set_x(this->contact_normal.get_z() * scale);
        contact_tangent[0].set_y(0.0f);
        contact_tangent[0].set_z(-this->contact_normal.get_x() * scale);

        contact_tangent[1].set_x(this->contact_normal.get_y() * contact_tangent[0].get_x());
        contact_tangent[1].set_y(
            this->contact_normal.get_z() * contact_tangent[0].get_x()
            - this->contact_normal.get_x() * contact_tangent[0].get_z()
        );
        contact_tangent[1].set_z(-this->contact_normal.get_y() * contact_tangent[0].get_x());
    } else {
        const float scale = 1.0f
            / std::sqrt(std::pow(this->contact_normal.get_z(), 2)
                        + std::pow(this->contact_normal.get_y(), 2));

        contact_tangent[0].set_x(0.0f);
        contact_tangent[0].set_y(-this->contact_normal.get_z() * scale);
        contact_tangent[0].set_z(this->contact_normal.get_y() * scale);

        contact_tangent[1].set_x(
            this->contact_normal.get_y() * contact_tangent[1].get_z()
            - this->contact_normal.get_z() * contact_tangent[0].get_y()
        );
        contact_tangent[1].set_y(-this->contact_normal.get_x() * contact_tangent[0].get_z());
        contact_tangent[1].set_z(this->contact_normal.get_x() * contact_tangent[0].get_y());
    }

    this->contact_to_world.set_column(0, this->contact_normal);
    this->contact_to_world.set_column(1, contact_tangent[0]);
    this->contact_to_world.set_column(2, contact_tangent[1]);
}

math::Vector3 Contact::calculate_frictionless_impulse(math::Matrix3& inverse_inertia_tensor) {
    math::Vector3 delta_vel_world = this->first_relative_contact_pos.cross(this->contact_normal)
                                        .transform(inverse_inertia_tensor)
                                        .cross(this->first_relative_contact_pos);

    float delta_velocity = delta_vel_world.dot(this->contact_normal);
    delta_velocity += this->first->get_inv_mass();

    if (this->second != nullptr) {
        math::Vector3 delta_vel_world =
            this->second_relative_contact_pos.cross(this->contact_normal)
                .transform(inverse_inertia_tensor)
                .cross(this->second_relative_contact_pos);

        delta_velocity += delta_vel_world.dot(this->contact_normal);
        delta_velocity += this->second->get_inv_mass();
    }

    return math::Vector3(this->desired_delta_velocity / delta_velocity, 0.0f, 0.0f);
}
