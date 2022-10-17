#include "../include/time.hpp"

using namespace std::chrono;

high_resolution_clock::time_point Time::last_frame = high_resolution_clock::now();
high_resolution_clock::time_point Time::current_frame = high_resolution_clock::now();
float Time::dt = 0.0f;

void Time::update() {
    current_frame = high_resolution_clock::now();
    Time::dt = duration<float, seconds::period>(current_frame - last_frame).count();
    last_frame = current_frame;
}

float Time::delta_time() {
    return Time::dt;
}
