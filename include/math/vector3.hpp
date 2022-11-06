#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <iostream>
#include <array>
#include <glm/glm.hpp>


namespace math {
    // Forward declaration of Matrix4
    class Matrix4;

    /* 
     * Class representing a mathematical vector in three dimensions
     */
    class Vector3 {
        private:
            std::array<float, 3> coords;

        public:
            Vector3(float x = 0.0, float y = 0.0, float z = 0.0);
            ~Vector3();

            void set_x(const float x);
            void set_y(const float y);
            void set_z(const float z);

            float get_x() const;
            float get_y() const;
            float get_z() const;

            float norm() const;
            Vector3 normalize() const;
            Vector3 invert() const;
            Vector3 transform(Matrix4 tranform_matrix);
            
            glm::vec3 to_glm_vec3();

            // Returns the vector data as a pointer to float;
            float* data();

            Vector3 operator+(const Vector3& rhs) const;
            Vector3& operator+=(const Vector3& rhs);
            Vector3 operator-(const Vector3& rhs) const;
            Vector3& operator-=(const Vector3& rhs);
            Vector3 operator*(const float& rhs) const;
            Vector3& operator*=(const float& rhs);
            Vector3 operator/(const float& rhs) const;
            Vector3& operator/=(const float& rhs);
            Vector3 operator-();

            float dot(const Vector3& rhs) const;
            Vector3 cross(const Vector3& rhs) const;

            friend std::ostream& operator<<(std::ostream& os, const Vector3& rhs);
            friend Vector3 operator*(float lhs, const math::Vector3& rhs);
    };
}

#endif // VECTOR3D_HPP
