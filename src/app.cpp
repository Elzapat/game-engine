#include "app.hpp"

void App::init() {
    const float rb_mass = 1000.0f;

    this->attached_body = std::make_shared<RigidBody>();
    attached_body->set_mass(rb_mass);
    attached_body->set_inertia_tensor(math::Matrix3(
        1.0f / 12.0f * rb_mass * (0.6 * 0.6 + 1.0f * 1.0f),
        1.0f / 12.0f * rb_mass * (2.0f * 2.0f + 1.0f * 1.0f),
        1.0f / 12.0f * rb_mass * (2.0f * 2.0f + 0.6f * 0.6f)
    ));

    this->anchor = std::make_shared<RigidBody>();
    this->anchor->set_position(math::Vector3(0.0f, 0.0f, 10.0f));
    this->anchor->set_mass(rb_mass);

    this->spring_visu = std::make_shared<RigidBody>();

    std::shared_ptr<RigidBody> rb3 = std::make_shared<RigidBody>(*this->attached_body);
    rb3->set_position(math::Vector3(0.0f, 10.0f, 0.0f));

    Mesh attached_body_mesh = Mesh::cube();
    attached_body_mesh.scale = math::Vector3(2.0f, 0.6f, 1.0f);
    attached_body_mesh.color =
        math::Vector3((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX);

    Mesh anchor_mesh = Mesh::sphere(1.0f, 20, 20);
    anchor_mesh.color =
        math::Vector3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, 1.0f);

    Mesh rb3_mesh = Mesh::cube();
    rb3_mesh.scale = math::Vector3(2.0f, 0.6f, 1.0f);
    rb3_mesh.color =
        math::Vector3(1.0f, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);

    std::unique_ptr<Spring> spring = std::make_unique<Spring>(
        math::Vector3(0.00f, 0.3f, 0.5f),
        this->anchor,
        math::Vector3(0.0f, 0.0f, 0.0f),
        500.0f,
        3.0f
    );
    std::unique_ptr<Gravity> gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));

    this->physic_world.force_registry.add_entry(this->attached_body, std::move(spring));
    this->physic_world.force_registry.add_entry(this->attached_body, std::move(gravity));

    this->physic_world.add_rigid_body(this->attached_body);
    this->physic_world.add_rigid_body(this->anchor);
    this->physic_world.add_rigid_body(rb3);
    /* this->physic_world.add_rigid_body(this->spring_visu); */

    this->renderer.add_mesh(attached_body_mesh);
    this->renderer.add_mesh(anchor_mesh);
    this->renderer.add_mesh(rb3_mesh);
    /* this->renderer.add_mesh(Mesh::cube()); */
}

void App::update() {
    static float time_elapsed = 0.0f;
    time_elapsed += Time::delta_time();

    if (time_elapsed >= 2.0f && time_elapsed <= 2.5f) {
        this->physic_world.get_rigid_bodies_ref()[2]->add_force_at_local_point(
            math::Vector3(100.0f, 5000.0f, 0.0f),
            math::Vector3(-0.5f, 0.5f, 0.3f)
        );
    }

    /*
    // Update spring visual
    this->renderer.remove_last_mesh();

    Mesh spring_visu_mesh = Mesh::cube();
    math::Vector3 from = this->anchor->get_position();
    math::Vector3 to =
        this->attached_body->get_point_in_world_space(math::Vector3(2.0f, 0.6f, 1.0f));
    math::Vector3 dir = from - to;
    this->spring_visu->set_position((from + to) / 2.0f);

    math::Vector3 up(0.0f, 0.0f, 1.0f);
    math::Vector3 axis = up.cross(dir);
    float angle =
        std::acos(
            (up.get_x() * dir.get_x() + up.get_y() * dir.get_y() + up.get_z() * dir.get_z())
            / std::sqrt(up.get_x() * up.get_x() + up.get_y() * up.get_y() + up.get_z() * up.get_z())
            * std::sqrt(

                dir.get_x() * dir.get_x() + dir.get_y() * dir.get_y() + dir.get_z() * dir.get_z()
            )
        )
        * M_PI / 180.0f;

    this->spring_visu->set_orientation(
        math::Quaternion(std::cos(angle), axis.normalize() * std::sin(angle))
    );

    spring_visu_mesh.scale = math::Vector3(0.1f, 0.1f, dir.norm() / 2.0f);
    spring_visu_mesh.color = math::Vector3(1.0f, 0.0f, 0.0f);

    this->renderer.add_mesh(spring_visu_mesh);
    */
}
