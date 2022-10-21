#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../math/vector3D.hpp"
#include "../time.hpp"

class Camera {
    public:
        Camera();
        void update();

        bool first_mouse = true;
        bool mouse_disabled = false;

        float speed = 3.0f;
        float sensitivity = 0.04f;

        struct {
            bool left = false;
            bool right = false;
            bool forwards = false;
            bool backwards = false;
            bool up = false;
            bool down = false;
        } keys;

        math::Vector3D rotation;
        math::Vector3D position;
        math::Vector3D front;
        math::Vector3D target;
        math::Vector3D direction;
        math::Vector3D up;
        math::Vector3D right;

        glm::mat4 view;
};

#endif // CAMERA_HPP
