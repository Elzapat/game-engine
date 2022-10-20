#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/math/vector3D.hpp"
#include "../include/time.hpp"
#include "../include/vulkan_renderer/vulkan_renderer.hpp"
#include "GLFW/glfw3.h"

int main() {
    srand(time(nullptr));

    try {
        VulkanRenderer vulkan_renderer;
        PhysicWorld physic_world;
        GLFWwindow* window;

        window = vulkan_renderer.init();

        while (!glfwWindowShouldClose(window)) {
            Time::update();
            float dt = Time::delta_time();

            glfwPollEvents();

            physic_world.update(dt);
            vulkan_renderer.update_camera();
            vulkan_renderer.draw();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
