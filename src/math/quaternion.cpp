#include "math/quaternion.hpp"

using namespace math;

Quaternion::Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

Quaternion::Quaternion(float _w, const Vector3 vec) :
    w(_w),
    x(vec.get_x()),
    y(vec.get_y()),
    z(vec.get_z()) {}

float Quaternion::get_w() const {
    return this->w;
}

float Quaternion::get_x() const {
    return this->x;
}

float Quaternion::get_y() const {
    return this->y;
}

float Quaternion::get_z() const {
    return this->z;
}

void Quaternion::set_w(const float w) {
    this->w = w;
}

void Quaternion::set_x(const float x) {
    this->x = x;
}

void Quaternion::set_y(const float y) {
    this->y = y;
}

void Quaternion::set_z(const float z) {
    this->z = z;
}

Quaternion Quaternion::normalize() {
    Quaternion res(*this);

    float &w = this->w, &x = this->x, &y = this->y, &z = this->z;
    float d = w * w + x * x + y * y + z * z;

    if (d == 0) {
        res.w = 1;
        return res;
    }

    d = 1.0f / std::sqrt(d);
    res.w *= d;
    res.x *= d;
    res.y *= d;
    res.z *= d;

    return res;
}

Quaternion Quaternion::rotate(const Vector3& rotation) {
    return *this * Quaternion(0.0f, rotation);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
    float w = this->w, x = this->x, y = this->y, z = this->z;
    Quaternion res;

    res.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    res.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    res.y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
    res.z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;

    return res;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
    *this = *this * rhs;

    return *this;
}

Quaternion Quaternion::operator+(const Vector3& rhs) const {
    Quaternion res(*this);

    Quaternion q(0.0f, rhs);
    q *= *this;

    res.w += q.w * 0.5f;
    res.x += q.x * 0.5f;
    res.y += q.y * 0.5f;
    res.z += q.z * 0.5f;

    return res;
}

Quaternion& Quaternion::operator+=(const Vector3& rhs) {
    *this = *this + rhs;

    return *this;
}
