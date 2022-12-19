#include "physics_engine/contacts/rigid_bodies/contact_resolver.hpp"

void ContactResolver::resolve_contacts(std::vector<Contact> contacts) {
    if (contacts.empty()) {
        return;
    }

    this->prepare_contacts(contacts);
    this->adjust_positions(contacts);
    this->adjust_velocities(contacts);
}

void ContactResolver::prepare_contacts(std::vector<Contact>& contacts) {
    for (Contact& contact : contacts) {
        contact.calculate_internals();
    }
}

void ContactResolver::adjust_positions(std::vector<Contact>& contacts) {
    std::array<math::Vector3, 2> linear_change, angular_change;

    for (int i = 0; i < this->iterations; i++) {
        Contact* worst_contact = nullptr;
        float worst_penetration = 0.0f;

        for (Contact& contact : contacts) {
            if (contact.penetration > worst_penetration) {
                worst_contact = &contact;
                worst_penetration = contact.penetration;
            }
        }

        if (worst_contact == nullptr) {
            break;
        }

        worst_contact->resolve_interpenetration(linear_change, angular_change, worst_penetration);

        for (Contact& contact : contacts) {
            for (int body_index = 0; body_index < 2; body_index++) {
                std::shared_ptr<RigidBody> body = contact.get_body(body_index);

                if (body == nullptr) {
                    continue;
                }

                for (int resolved_body_index = 0; resolved_body_index < 2; resolved_body_index++) {
                    std::shared_ptr<RigidBody> resolved_body =
                        contact.get_body(resolved_body_index);

                    if (body.get() != worst_contact->get_body(resolved_body_index).get()) {
                        continue;
                    }

                    math::Vector3 delta_position = linear_change[resolved_body_index]
                        + angular_change[resolved_body_index].cross(
                            contact.relative_contact_pos[body_index]
                        );

                    contact.penetration += delta_position.dot(contact.contact_normal)
                        * (body_index == 1 ? 1.0f : -1.0f);
                }
            }
        }
    }
}

void ContactResolver::adjust_velocities(std::vector<Contact>& contacts) {
    std::array<math::Vector3, 2> velocity_change, rotation_change;

    for (int i = 0; i < this->iterations; i++) {
        Contact* max_vel_contact = nullptr;
        float max_vel = -std::numeric_limits<float>().max();

        for (Contact& contact : contacts) {
            if (contact.desired_delta_velocity > max_vel) {
                max_vel = contact.desired_delta_velocity;
                max_vel_contact = &contact;
            }
        }

        if (max_vel_contact == nullptr) {
            break;
        }

        max_vel_contact->resolve_velocity(velocity_change, rotation_change);

        for (Contact& contact : contacts) {
            for (int body_index = 0; body_index < 2; body_index++) {
                std::shared_ptr<RigidBody> body = contact.get_body(body_index);

                if (body == nullptr) {
                    continue;
                }

                for (int resolved_body_index = 0; resolved_body_index < 2; resolved_body_index++) {
                    std::shared_ptr<RigidBody> resolved_body =
                        contact.get_body(resolved_body_index);

                    if (body.get() != max_vel_contact->get_body(resolved_body_index).get()) {
                        continue;
                    }

                    math::Vector3 delta_vel = velocity_change[resolved_body_index]
                        + rotation_change[resolved_body_index].cross(
                            contact.relative_contact_pos[body_index]
                        );

                    contact.contact_velocity += (body_index == 0 ? 1.0f : -1.0f)
                        * delta_vel.transform(contact.contact_to_world.transpose());

                    contact.calculate_desired_delta_velocity();
                }
            }
        }
    }
}
