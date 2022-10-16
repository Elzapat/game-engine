#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <iostream>
#include <array>
#include <glm/glm.hpp>

namespace math {
    /* 
     * Class representing a mathematical vector in three dimensions
     */
    class Vector3D {
        private:
            std::array<float, 3> coords;

        public:
            Vector3D(float x = 0.0, float y = 0.0, float z = 0.0);
            ~Vector3D();

            void set_x(const float x);
            void set_y(const float y);
            void set_z(const float z);

            float get_x() const;
            float get_y() const;
            float get_z() const;

            float norm() const;
            Vector3D normalize();
            Vector3D invert();
            Vector3D translate(Vector3D const& translation);
            // TODO: when Quaternions are implemented
            // Vector3D rotate(Quaternion rotation) ;
            Vector3D scale(const float scale);
            glm::vec3 to_glm_vec3();

            // Returns the vector data as a pointer to float;
            float* data();

            Vector3D operator+(const Vector3D& rhs) const;
            Vector3D& operator+=(const Vector3D& rhs);
            Vector3D operator-(const Vector3D& rhs) const;
            Vector3D& operator-=(const Vector3D& rhs);
            Vector3D operator*(const float& rhs) const;
            Vector3D& operator*=(const float& rhs);

            float dot(const Vector3D& rhs) const;
            Vector3D cross(const Vector3D& rhs) const;

            friend std::ostream& operator<<(std::ostream& os, const Vector3D& rhs);
    };
}

#endif // VECTOR3D_HPP
