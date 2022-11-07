#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include <cmath>
#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include <algorithm>
#include "vector3.hpp"
#include "quaternion.hpp"

namespace math {
    /* 
     * Class representing a mathematical matrix 3x3
     */
    class Matrix3 {
        private:
            std::array<float, 9> values;

        public:
            Matrix3(
                float x1 = 0.0, float y1 = 0.0, float z1 =0.0,
                float x2 = 0.0, float y2 = 0.0, float z2 =0.0,
                float x3 = 0.0, float y3 = 0.0, float z3 =0.0
            );
            ~Matrix3();

            std::array<float, 9> get_values() const;
            std::array<float, 9>& get_values_ref();
            Vector3 get_line(int line) const;
            Vector3 get_column(int column) const;
            float get_value(const int line, const int column) const;

            void set_value(int line, int column, float value);
            void set_values(std::array<float, 9> values);

            void set_line(int line, Vector3 vect_line);
            void set_column(int column, Vector3 vect_column);

            Matrix3 operator*(const Matrix3& other) const;
            Vector3 operator*(const Vector3& other) const;

            float get_det() const;
            Matrix3 inverse() const;
            Matrix3 transpose() const;

            void set_orientation(const Quaternion& q);

    };
}

#endif // MATRIX3_HPP
