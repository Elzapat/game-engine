#include "app.hpp"

void App::init() {
    std::shared_ptr<RigidBody> rb = std::make_shared<RigidBody>();
    /* rb->set_orientation(math::Quaternion(1.0f, 0.5f, 1.0f, 2.0f)); */
    /* rb->set_angular_velocity(math::Vector3(20.1f, 20.1f, 20.1f)); */
    rb->set_mass(50.0f);
    // rb->set_linear_velocity(math::Vector3(0.5f, 1.0f, 2.0f));

    std::shared_ptr<RigidBody> rb2 = std::make_shared<RigidBody>();
    rb2->set_posisition(math::Vector3(1.0f, 5.0f, 10.0f));
    rb2->set_mass(50.0f);

    Mesh rb_mesh = Mesh::cube();
    rb_mesh.scale = math::Vector3(2.0f, 0.6f, 1.0f);
    Mesh rb2_mesh = Mesh::sphere(1.0f, 20, 20);

    std::unique_ptr<Spring> spring = std::make_unique<Spring>(
        math::Vector3(0.0f, 0.0f, 0.0f),
        rb2,
        math::Vector3(-1.0f, -1.0f, -0.0f),
        50.0f,
        3.0f
    );
    std::unique_ptr<Gravity> gravity = std::make_unique<Gravity>(math::Vector3(0.0f, 0.0f, -9.81f));

    this->physic_world.force_registry.add_entry(rb, std::move(spring));
    this->physic_world.force_registry.add_entry(rb, std::move(gravity));

    this->physic_world.add_rigid_body(rb);
    this->physic_world.add_rigid_body(rb2);

    this->renderer.add_mesh(rb_mesh);
    this->renderer.add_mesh(rb2_mesh);
}

void App::update() {}
