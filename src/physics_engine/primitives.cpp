#include "physics_engine/primitives.hpp"

math::Matrix4 Primitive::get_transform() const {
    return this->rigid_body->get_transform() * this->offset;
}

math::Vector3 Primitive::get_axis(int i) const {
    return this->get_transform().get_axis_vector(i);
}