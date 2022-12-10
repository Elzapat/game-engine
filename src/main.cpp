#include "app.hpp"
#include "test_scenes/test_cable.hpp"

int main(int argc, char** argv) {
    if (argc == 1) {
        return App().run();
    } else if (std::string(argv[1]) == "TestCable") {
        return TestCable().run();
    }
}
