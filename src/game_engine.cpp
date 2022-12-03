#include "game_engine.hpp"

GameEngine::GameEngine() {
    srand(time(nullptr));

    this->window = renderer.init();
}

GameEngine::~GameEngine() {
    for (int i = this->objects.size() - 1; i >= 0; i--) {
        this->remove_object(static_cast<size_t>(i));
    }
}

void GameEngine::add_object(Object object) {
    this->renderer.init_mesh(object.get_mesh());
    this->objects.push_back(std::move(object));
}

void GameEngine::remove_object(size_t index) {
    this->renderer.cleanup_mesh(this->objects[index].get_mesh());
    this->objects.erase(this->objects.begin() + index);
}

void GameEngine::init() {}

void GameEngine::update() {}

void GameEngine::cleanup() {}

void GameEngine::update_backend() {
    Time::update();
    glfwPollEvents();

    physic_world.update(this->objects);
    renderer.update_camera();
    renderer.draw(this->objects);
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
        this->cleanup();
        return EXIT_FAILURE;
    }

    this->cleanup();
    return EXIT_SUCCESS;
}
