#include "../include/vector3D.hpp"

Vector3D::Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
Vector3D::~Vector3D() {}

void Vector3D::set_x(const float x) {
    this->x = x;
}

void Vector3D::set_y(const float y) {
    this->y = y;
}

void Vector3D::set_z(const float z) {
    this->z = z;
}

float Vector3D::get_x() const {
    return this->x;
}

float Vector3D::get_y() const {
    return this->y;
}

float Vector3D::get_z() const {
    return this->z;
}

float Vector3D::norm() const {
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
}

void Vector3D::normalize() {
    float norm = this->norm();

    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
}

void Vector3D::invert() {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

/* void translate(Vector3D const& translation) ; */
/* // TODO: when Quaternions are implemented */
/* // void rotate(Quaternion rotation) ; */
/* void scale(float scale) ; */
/*  */

Vector3D Vector3D::operator+(const Vector3D& rhs) const {
    return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    /* return Vector3D(*this) += rhs; */
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const {
    return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3D Vector3D::operator*(const float& rhs) const {
    Vector3D res = Vector3D(*this);

    res.x *= rhs;
    res.y *= rhs;
    res.z *= rhs;

    return res;
}

Vector3D& Vector3D::operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;

    return *this;
}

float Vector3D::dot(const Vector3D& rhs) const {
    return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
}

Vector3D Vector3D::cross(const Vector3D& rhs) const {
    return Vector3D(
        this->y * rhs.z - this->z * rhs.y,
        this->z * rhs.x - this->x * rhs.z,
        this->x * rhs.y - this->y * rhs.x
    );
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "Vector3D { x = " << vec.get_x() << ", y = " << vec.get_y() << ", z = " << vec.get_z()
       << " }";

    return os;
}
