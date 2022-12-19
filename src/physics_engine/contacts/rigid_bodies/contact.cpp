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

void Contact::swap_bodies() {
    this->contact_normal *= -1.0f;

    std::shared_ptr<RigidBody> temp = this->first;
    this->first = this->second;
    this->second = temp;
}

void Contact::calculate_internals() {
    if (first == nullptr) {
        this->swap_bodies();
    }

    if (first == nullptr) {
        throw std::runtime_error("Both rigidbodies are nullptr in calculate_internals()");
    }

    this->calculate_contact_basis();

    this->relative_contact_pos[0] = this->contact_point - first->get_position();
    if (this->second != nullptr) {
        this->relative_contact_pos[1] = this->contact_point - second->get_position();
    }

    this->contact_velocity = this->calculate_local_velocity(first, this->relative_contact_pos[0]);
    if (this->second != nullptr) {
        this->contact_velocity -=
            this->calculate_local_velocity(second, this->relative_contact_pos[1]);
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
    if (second != nullptr) {
        vel_from_acc -= (second->get_acceleration() * Time::delta_time()).dot(this->contact_normal);
    }

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
            this->contact_normal.get_y() * contact_tangent[0].get_z()
            - this->contact_normal.get_z() * contact_tangent[0].get_y()
        );
        contact_tangent[1].set_y(-this->contact_normal.get_x() * contact_tangent[0].get_z());
        contact_tangent[1].set_z(this->contact_normal.get_x() * contact_tangent[0].get_y());
    }

    this->contact_to_world.set_column(0, this->contact_normal);
    this->contact_to_world.set_column(1, contact_tangent[0]);
    this->contact_to_world.set_column(2, contact_tangent[1]);
}

math::Vector3
Contact::calculate_frictionless_impulse(std::array<math::Matrix3, 2> inverse_inertia_tensors) {
    math::Vector3 delta_vel_world = this->relative_contact_pos[0]
                                        .cross(this->contact_normal)
                                        .transform(inverse_inertia_tensors[0])
                                        .cross(this->relative_contact_pos[0]);

    float delta_velocity = delta_vel_world.dot(this->contact_normal);
    delta_velocity += this->first->get_inv_mass();

    if (this->second != nullptr) {
        math::Vector3 delta_vel_world = this->relative_contact_pos[1]
                                            .cross(this->contact_normal)
                                            .transform(inverse_inertia_tensors[1])
                                            .cross(this->relative_contact_pos[1]);

        delta_velocity += delta_vel_world.dot(this->contact_normal);
        delta_velocity += this->second->get_inv_mass();
    }

    return math::Vector3(this->desired_delta_velocity / delta_velocity, 0.0f, 0.0f);
}

std::shared_ptr<RigidBody> Contact::get_body(int index) {
    if (index == 0) {
        return this->first;
    } else if (index == 1) {
        return this->second;
    } else {
        return nullptr;
    }
}

void Contact::resolve_interpenetration(
    std::array<math::Vector3, 2>& linear_change,
    std::array<math::Vector3, 2>& angular_change,
    float penetration
) {
    const float angular_limit = 0.2f;
    std::array<float, 2> linear_move, angular_move;

    float total_inertia = 0;
    std::array<float, 2> linear_inertia, angular_inertia;

    std::array<std::shared_ptr<RigidBody>, 2> bodies = {this->first, this->second};

    for (int i = 0; i < 2; i++) {
        if (bodies[i] == nullptr) {
            continue;
        }

        math::Matrix3 inverse_inertia_tensor = bodies[i]->get_inverse_inertia_tensor_world();

        math::Vector3 angular_inertia_world = this->relative_contact_pos[i]
                                                  .cross(this->contact_normal)
                                                  .transform(inverse_inertia_tensor)
                                                  .cross(this->relative_contact_pos[i]);

        angular_inertia[i] = angular_inertia_world.dot(this->contact_normal);
        linear_inertia[i] = bodies[i]->get_inv_mass();

        total_inertia += linear_inertia[i] + angular_inertia[i];
    }

    for (int i = 0; i < 2; i++) {
        if (bodies[i] == nullptr) {
            continue;
        }

        float sign = i == 0 ? 1.0f : -1.0f;
        angular_move[i] = sign * penetration * (angular_inertia[i] / total_inertia);
        linear_move[i] = sign * penetration * (linear_inertia[i] / total_inertia);

        math::Vector3 projection = this->relative_contact_pos[i]
            + this->contact_normal * -relative_contact_pos[i].dot(this->contact_normal);

        float max_magnitude = angular_limit * projection.norm();

        if (angular_move[i] < -max_magnitude) {
            float total_move = angular_move[i] + linear_move[i];
            angular_move[i] = -max_magnitude;
            linear_move[i] = total_move - angular_move[i];
        } else if (angular_move[i] > max_magnitude) {
            float total_move = angular_move[i] + linear_move[i];
            angular_move[i] = max_magnitude;
            linear_move[i] = total_move - angular_move[i];
        }

        if (angular_move[i] == 0.0f) {
            angular_change[i] = math::Vector3(0.0f, 0.0f, 0.0f);
        } else {
            math::Vector3 target_angular_direction =
                this->relative_contact_pos[i].cross(this->contact_normal);
            math::Matrix3 inverse_inertia_tensor = bodies[i]->get_inverse_inertia_tensor();

            angular_change[i] = target_angular_direction.transform(inverse_inertia_tensor)
                * (angular_move[i] / angular_inertia[i]);
        }

        linear_change[i] = this->contact_normal * linear_move[i];

        math::Vector3 pos = bodies[i]->get_position() + (this->contact_normal * linear_move[i]);
        bodies[i]->set_position(pos);

        math::Quaternion q = bodies[i]->get_orientation() + angular_change[i];
        bodies[i]->set_orientation(q);
    }
}

void Contact::resolve_velocity(
    std::array<math::Vector3, 2>& velocity_change,
    std::array<math::Vector3, 2>& rotation_change
) {
    std::array<math::Matrix3, 2> inverse_inertia_tensors;

    inverse_inertia_tensors[0] = this->first->get_inverse_inertia_tensor_world();
    if (this->second != nullptr) {
        inverse_inertia_tensors[1] = this->second->get_inverse_inertia_tensor_world();
    }

    math::Vector3 impulse_contact;

    if (this->friction == 0.0f) {
        impulse_contact = this->calculate_frictionless_impulse(inverse_inertia_tensors);
    } else {
        throw std::runtime_error("Contact with friction not implemented yet!");
    }

    math::Vector3 impulse = impulse_contact.transform(this->contact_to_world);

    math::Vector3 torque_impulse = this->relative_contact_pos[0].cross(impulse);
    rotation_change[0] = torque_impulse.transform(inverse_inertia_tensors[0]);
    velocity_change[0] = impulse * first->get_inv_mass();

    this->first->apply_impulse(velocity_change[0]);
    this->first->apply_torque_impulse(rotation_change[0]);

    if (this->second == nullptr) {
        return;
    }

    torque_impulse = impulse.cross(relative_contact_pos[1]);
    rotation_change[1] = torque_impulse.transform(inverse_inertia_tensors[1]);
    velocity_change[1] = impulse * -this->second->get_inv_mass();

    this->second->apply_impulse(velocity_change[1]);
    this->second->apply_torque_impulse(rotation_change[1]);
}
