#include "object.hpp"

Object::Object(std::shared_ptr<RigidBody> rb, Mesh m) : rigid_body(rb), mesh(m) {}

Mesh& Object::get_mesh() {
    return this->mesh;
}

std::shared_ptr<RigidBody> Object::get_rigid_body() {
    return this->rigid_body;
}
