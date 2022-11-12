#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <ctime>
#include <exception>

#include "GLFW/glfw3.h"
#include "vulkan_renderer/vulkan_renderer.hpp"
#include "physics_engine/physic_world.hpp"

class GameEngine {
    private:
        void update_backend();
        virtual void update() = 0;
        virtual void init() = 0;

    protected:
        VulkanRenderer renderer;
        PhysicWorld physic_world;
        GLFWwindow* window;

    public:
        GameEngine();
        ~GameEngine();
        
        int run();

};

#endif // GAME_ENGINE_HPP
