#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/math/vector3D.hpp"
#include "../include/physics_engine/particle.hpp"
#include "../include/physics_engine/particle_force_registry.hpp"
#include "../include/physics_engine/particle_spring.hpp"
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
            glfwPollEvents();

            physic_world.update();
            vulkan_renderer.update_camera();
            vulkan_renderer.draw(physic_world.get_particles_ref());
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
