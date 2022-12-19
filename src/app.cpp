#include "app.hpp"

void App::init() {
    const float rb_mass = 5000.0f;

    std::shared_ptr<RigidBody> attached_body_rb = std::make_shared<RigidBody>();
    attached_body_rb->set_mass(rb_mass);
    attached_body_rb->set_inertia_tensor(math::Matrix3(
        1.0f / 12.0f * rb_mass * (0.6 * 0.6 + 1.0f * 1.0f),
        1.0f / 12.0f * rb_mass * (2.0f * 2.0f + 1.0f * 1.0f),
        1.0f / 12.0f * rb_mass * (2.0f * 2.0f + 0.6f * 0.6f)
    ));
    attached_body_rb->set_bounding_radius(2.0f);

    Mesh attached_body_mesh = Mesh::cube();
    attached_body_mesh.scale = math::Vector3(2.0f, 0.6f, 1.0f);
    attached_body_mesh.color =
        math::Vector3((float)rand() / (float)RAND_MAX, 1.0f, (float)rand() / (float)RAND_MAX);

    std::shared_ptr<Box> attached_body_box = std::make_shared<Box>();
    attached_body_box->half_size = math::Vector3(1.0f, 0.3f, 0.5f);
    attached_body_box->rigid_body = attached_body_rb;

    attached_body_rb->set_collision_volume(attached_body_box);

    Object attached_body(attached_body_rb, attached_body_mesh);

    std::shared_ptr<RigidBody> anchor_rb = std::make_shared<RigidBody>();
    anchor_rb->set_position(math::Vector3(0.0f, 5.0f, 10.0f));
    anchor_rb->set_mass(rb_mass);
    anchor_rb->set_bounding_radius(1.0f);
    // anchor_rb->apply_impulse(math::Vector3(0.0f, 0.0f, -10.0f));

    Mesh anchor_mesh = Mesh::sphere(1.0f, 20, 20);
    anchor_mesh.color = math::Vector3(0.0f, 0.0f, 1.0f);

    std::shared_ptr<Sphere> anchor_sphere = std::make_shared<Sphere>();
    anchor_sphere->radius = 1.0f;
    anchor_sphere->rigid_body = anchor_rb;

    anchor_rb->set_collision_volume(anchor_sphere);

    Object anchor(anchor_rb, anchor_mesh);

    std::shared_ptr<RigidBody> rb3 = std::make_shared<RigidBody>(*attached_body_rb);
    rb3->set_position(math::Vector3(-20.0f, 20.0f, 0.0f));
    rb3->set_bounding_radius(2.0f);

    Mesh rb3_mesh = Mesh::cube();
    rb3_mesh.scale = math::Vector3(2.0f, 0.6f, 1.0f);
    rb3_mesh.color =
        math::Vector3(1.0f, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);

    std::shared_ptr<Box> rb3_box = std::make_shared<Box>();
    rb3_box->half_size = math::Vector3(1.0f, 0.3f, 0.5f);
    rb3_box->rigid_body = rb3;

    rb3->set_collision_volume(rb3_box);

    Object rb3_object = Object(rb3, rb3_mesh);

    std::shared_ptr<RigidBody> plane_rb = std::make_shared<RigidBody>();
    plane_rb->set_position(math::Vector3(0.0f, 0.0f, -20.0f));
    plane_rb->set_mass(50.0f);
    plane_rb->set_bounding_radius(1000.0f);

    Mesh plane_mesh = Mesh::cube();
    plane_mesh.scale = math::Vector3(1000.0f, 1000.0f, 0.0001f);
    plane_mesh.color = math::Vector3(1.0f, 1.0f, 1.0f);

    std::shared_ptr<Plane> plane_collision = std::make_shared<Plane>();
    plane_collision->rigid_body = nullptr;
    plane_collision->normal = math::Vector3(0.0f, 0.0f, 1.0f);
    plane_collision->offset = -20.0f;
    plane_rb->set_collision_volume(plane_collision);

    Object plane = Object(plane_rb, plane_mesh);

    this->add_object(rb3_object);
    // this->add_object(attached_body);
    this->add_object(anchor);
    this->add_object(plane);

    for (int i = 0; i < 20; i++) {
        std::shared_ptr<RigidBody> rb = std::make_shared<RigidBody>();
        rb->set_position(math::Vector3(0.0f, 5.0f, 15.0f * (float)i));
        rb->set_mass(1000.0f);
        rb->set_bounding_radius(1.0f);

        Mesh mesh = Mesh::sphere(1.0f, 20, 20);
        mesh.color = math::Vector3((float)(i < 10), 1.0f, 0.0f);

        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
        sphere->radius = 1.0f;
        sphere->rigid_body = rb;

        rb->set_collision_volume(sphere);

        this->add_object(Object(rb, mesh));

        std::unique_ptr<Gravity> gravity =
            std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));

        this->physic_world.force_registry.add_entry(rb, std::move(gravity));
        if (i < 10) {
            std::unique_ptr<Spring> spring = std::make_unique<Spring>(
                math::Vector3(0.00f, 0.3f, 0.5f),
                anchor_rb,
                math::Vector3(0.0f, 0.0f, 0.0f),
                500.0f,
                3.0f
            );
            this->physic_world.force_registry.add_entry(rb, std::move(spring));
        }
    }

    std::unique_ptr<Spring> spring = std::make_unique<Spring>(
        math::Vector3(0.00f, 0.3f, 0.5f),
        anchor_rb,
        math::Vector3(0.0f, 0.0f, 0.0f),
        500.0f,
        3.0f
    );
    std::unique_ptr<Gravity> gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));

    // this->physic_world.force_registry.add_entry(attached_body_rb, std::move(spring));
    this->physic_world.force_registry.add_entry(attached_body_rb, std::move(gravity));
    gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));
    this->physic_world.force_registry.add_entry(anchor_rb, std::move(gravity));
    gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));
    this->physic_world.force_registry.add_entry(rb3, std::move(gravity));
}

void App::update() {
    static float time_elapsed = 0.0f;
    time_elapsed += Time::delta_time();

    // if (time_elapsed >= 2.0f && time_elapsed <= 2.5f) {
    //     this->objects[0].get_rigid_body()->add_force_at_local_point(
    //         math::Vector3(100.0f, 5000.0f, 0.0f),
    //         math::Vector3(-0.5f, 0.5f, 0.3f)
    //     );
    // }

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

void App::cleanup() {}
