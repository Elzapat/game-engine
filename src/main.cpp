#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/math/vector3D.hpp"
#include "../include/vulkan_renderer/vulkan_renderer.hpp"
#include "GLFW/glfw3.h"

int main() {
    srand(time(nullptr));

    try {
        using namespace std::chrono;

        VulkanRenderer vulkan_renderer;
        PhysicWorld physic_world;
        GLFWwindow* window;

        window = vulkan_renderer.init();

        auto last_frame = high_resolution_clock::now();
        auto current_frame = high_resolution_clock::now();

        while (!glfwWindowShouldClose(window)) {
            current_frame = high_resolution_clock::now();
            float dt = duration<float, seconds::period>(current_frame - last_frame).count();
            last_frame = current_frame;

            glfwPollEvents();

            physic_world.update(dt);
            vulkan_renderer.draw();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
