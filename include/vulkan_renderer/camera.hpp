#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../math/vector3.hpp"
#include "../time.hpp"

class Camera {
    public:
        Camera();
        void update();

        bool first_mouse = true;
        bool mouse_disabled = false;

        float speed = 15.0f;
        float sensitivity = 0.04f;

        struct {
            bool left = false;
            bool right = false;
            bool forwards = false;
            bool backwards = false;
            bool up = false;
            bool down = false;
        } keys;

        math::Vector3 rotation;
        math::Vector3 position;
        math::Vector3 front;
        math::Vector3 target;
        math::Vector3 direction;
        math::Vector3 up;
        math::Vector3 right;

        glm::mat4 view;
};

#endif // CAMERA_HPP
