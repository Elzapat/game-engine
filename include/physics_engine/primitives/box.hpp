#ifndef BOX_HPP
#define BOX_HPP

#include "math/Vector3.hpp"

class Box
{
private:
    math::Vector3 half_size;
public:
    Box(/* args */);
    ~Box();
};

#endif
