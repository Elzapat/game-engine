#include "game_engine.hpp"

GameEngine::GameEngine() {
    srand(time(nullptr));

    this->window = renderer.init();
}

GameEngine::~GameEngine() {}

void GameEngine::update() {}

void GameEngine::update_backend() {
    Time::update();
    glfwPollEvents();

    physic_world.update();
    renderer.update_camera();
    renderer.draw(physic_world.get_particles_ref(), physic_world.get_rigid_bodies_ref());
}

int GameEngine::run() {
    this->init();

    try {
        while (!glfwWindowShouldClose(this->window)) {
            this->update_backend();
            this->update();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
