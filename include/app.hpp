#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "game_engine.hpp"

class App : public GameEngine {
    private:
        virtual void init() override;
        virtual void update() override;

        std::shared_ptr<RigidBody> anchor;
        std::shared_ptr<RigidBody> attached_body;
        std::shared_ptr<RigidBody> spring_visu;
};

#endif // APPLICATION_HPP
