#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "game_engine.hpp"

class App : public GameEngine {
    private:
        virtual void init() override;
        virtual void update() override;
        virtual void cleanup() override;
};

#endif // APPLICATION_HPP
