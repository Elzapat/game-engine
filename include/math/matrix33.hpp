#ifndef Matrix33_HPP
#define Matrix33_HPP

#include <cmath>
#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include "vector3D.hpp"

namespace math {
    /* 
     * Class representing a mathematical matrix 3x3
     */
    class Matrix33 {
        private:
            std::array<float, 9> values;

        public:
            Matrix33(
                float x1 = 0.0, float y1 = 0.0, float z1 =0.0,
                float x2 = 0.0, float y2 = 0.0, float z2 =0.0,
                float x3 = 0.0, float y3 = 0.0, float z3 =0.0
            );
            ~Matrix33();

            std::array<float, 9> get_values();
            Vector3D get_line(int line);
            Vector3D get_column(int column);
            float get_value(int line, int column);

            void set_value(int line, int column, float value);
            void set_values(std::array<float, 9> values);

            void set_line(int line, Vector3D vect_line);
            void set_column(int column, Vector3D vect_column);

            Matrix33 operator*(const Matrix33& other) const;
            Vector3D operator*(const Vector3D& other) const;

            Matrix33 inverse();
            Matrix33 transpose();

            void setOrientation(const Quaternion& q);

    };
}

#endif // VECTOR3D_HPP
