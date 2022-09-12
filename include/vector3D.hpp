#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <iostream>

/* 
 * Class representing a mathematical vector in three dimensions
 */
class Vector3D {
    private:
        float x, y, z;

    public:
        Vector3D(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0) noexcept;
        ~Vector3D();

        void set_x(const float x) noexcept;
        void set_y(const float y) noexcept;
        void set_z(const float z) noexcept;

        float get_x() const noexcept;
        float get_y() const noexcept;
        float get_z() const noexcept;

        float norm() const noexcept;
        void normalize() noexcept;
        void invert() noexcept;
        void translate(const Vector3D translation) noexcept;
        // TODO: when Quaternions are implemented
        // void rotate(Quaternion rotation) noexcept;
        void scale(const float scale) noexcept;

        Vector3D operator+(const Vector3D& rhs) const noexcept;
        Vector3D& operator+=(const Vector3D& rhs) noexcept;
        Vector3D operator-(const Vector3D& rhs) const noexcept;
        Vector3D& operator-=(const Vector3D& rhs) noexcept;
        Vector3D operator*(const float& rhs) const noexcept;
        Vector3D& operator*=(const float& rhs) noexcept;

        float dot(const Vector3D& rhs) const noexcept;
        Vector3D cross(const Vector3D& rhs) const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Vector3D& rhs);
};

#endif  // VECTOR3D_HPP
