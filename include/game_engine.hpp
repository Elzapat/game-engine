#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <ctime>
#include <exception>

#include "GLFW/glfw3.h"
#include "vulkan_renderer/vulkan_renderer.hpp"
#include "physics_engine/physic_world.hpp"
#include "object.hpp"
#include "physics_engine/collisions/node.hpp"

class GameEngine {
    private:
        void update_backend();
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void cleanup() = 0;

    protected:
        VulkanRenderer renderer;
        PhysicWorld physic_world;
        GLFWwindow* window;
        std::vector<Object> objects;
        std::shared_ptr<Node> octree;

        void add_object(Object object);
        void remove_object(size_t index);

    public:
        GameEngine();
        ~GameEngine();
        
        int run();
};

#endif // GAME_ENGINE_HPP
