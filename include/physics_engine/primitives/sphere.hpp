#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "primitive.hpp"

class Sphere : public Primitive
{
private:
    float radius;
public:
    Sphere(/* args */);
    ~Sphere();
};


#endif