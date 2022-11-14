#ifndef TEST_CABLE_HPP
#define TEST_CABLE_HPP

#include "game_engine.hpp"

class TestCable : public GameEngine {
    private:
        virtual void init() override;
        virtual void update() override;
};

#endif // TEST_CABLE_HPP
