#include "../../include/vulkan_renderer/camera.hpp"

Camera::Camera() {
    this->position = math::Vector3D(5.0f, 5.0f, 0.0f);
    this->front = math::Vector3D(0.0f, 1.0f, 0.0f);

    this->direction = (this->position - this->target).normalize();

    this->right = math::Vector3D(0.0f, 0.0f, 1.0f).cross(this->direction).normalize();

    this->up = this->direction.cross(this->right);

    this->update(0.0f);
}

void Camera::update(float dt) {
    // Update looking direction
    math::Vector3D direction(
        std::cos(glm::radians(this->rotation.get_x()))
            * std::cos(glm::radians(this->rotation.get_z())),
        -std::sin(glm::radians(this->rotation.get_x()))
            * std::cos(glm::radians(this->rotation.get_z())),
        -std::sin(glm::radians(this->rotation.get_z()))
    );
    this->front = direction.normalize();

    // Update position
    if (this->keys.forwards) {
        this->position += this->front * this->speed * dt;
    }

    if (this->keys.backwards) {
        this->position -= this->front * this->speed * dt;
    }

    if (this->keys.right) {
        this->position += this->front.cross(this->up).normalize() * this->speed * dt;
    }

    if (this->keys.left) {
        this->position -= this->front.cross(this->up).normalize() * this->speed * dt;
    }

    if (this->keys.up) {
        this->position -= this->front.cross(this->right).normalize() * this->speed * dt;
    }

    if (this->keys.down) {
        this->position += this->front.cross(this->right).normalize() * this->speed * dt;
    }

    this->view = glm::lookAt(
        this->position.to_glm_vec3(),
        (this->position + this->front).to_glm_vec3(),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
}
