#include <iostream>

#include "../include/vector3D.hpp"

int main() {
    std::cout << "operator+= test" << std::endl;
    std::cout << (Vector3D() += Vector3D(1.0, 1.0, 2.0)) << std::endl;

    std::cout << "\ndot product test" << std::endl;
    std::cout << Vector3D(1.0, 0.0, 0.0).dot(Vector3D(0.0, 1.0, 0.0)) << std::endl;
    std::cout << Vector3D(1.0, 0.0, 0.0).dot(Vector3D(1.0, 0.0, 0.0)) << std::endl;

    std::cout << "\ncross product test" << std::endl;
    std::cout << Vector3D(1.0, 0.0, 0.0).cross(Vector3D(0.0, 1.0, 0.0)) << std::endl;

    return 0;
}
