#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time {
    public:
        static void update();
        static float delta_time();

    private:
        static std::chrono::high_resolution_clock::time_point last_frame;
        static std::chrono::high_resolution_clock::time_point current_frame;
        static float dt;
};

#endif // TIME_HPP
