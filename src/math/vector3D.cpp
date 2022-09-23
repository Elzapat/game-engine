#include "../../include/math/vector3D.hpp"

using namespace math;

Vector3D::Vector3D(float x, float y, float z) : coords({x, y, z}) {}
Vector3D::~Vector3D() {}

void Vector3D::set_x(const float x) {
    this->coords[0] = x;
}

void Vector3D::set_y(const float y) {
    this->coords[1] = y;
}

void Vector3D::set_z(const float z) {
    this->coords[2] = z;
}

float Vector3D::get_x() const {
    return this->coords[0];
}

float Vector3D::get_y() const {
    return this->coords[1];
}

float Vector3D::get_z() const {
    return this->coords[2];
}

float Vector3D::norm() const {
    return std::sqrt(
        std::pow(this->get_x(), 2) + std::pow(this->get_y(), 2) + std::pow(this->get_z(), 2)
    );
}

void Vector3D::normalize() {
    float norm = this->norm();

    this->coords[0] /= norm;
    this->coords[1] /= norm;
    this->coords[2] /= norm;
}

void Vector3D::invert() {
    this->coords[0] = -this->coords[0];
    this->coords[1] = -this->coords[1];
    this->coords[2] = -this->coords[2];
}

/* void translate(Vector3D const& translation) ; */
/* // TODO: when Quaternions are implemented */
/* // void rotate(Quaternion rotation) ; */
/* void scale(float scale) ; */
/*  */

float* Vector3D::data() {
    return this->coords.data();
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const {
    return Vector3D(
        this->coords[0] + rhs.coords[0],
        this->coords[1] + rhs.coords[1],
        this->coords[2] + rhs.coords[2]
    );
    /* return Vector3D(*this) += rhs; */
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const {
    return Vector3D(
        this->get_x() - rhs.get_x(),
        this->get_y() - rhs.get_y(),
        this->get_z() - rhs.get_z()
    );
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3D Vector3D::operator*(const float& rhs) const {
    Vector3D res = Vector3D(*this);

    res.coords[0] *= rhs;
    res.coords[1] *= rhs;
    res.coords[2] *= rhs;

    return res;
}

Vector3D& Vector3D::operator*=(const float& rhs) {
    this->coords[0] *= rhs;
    this->coords[1] *= rhs;
    this->coords[2] *= rhs;

    return *this;
}

float Vector3D::dot(const Vector3D& rhs) const {
    return this->get_x() * rhs.get_x() + this->get_y() * rhs.get_y() + this->get_z() * rhs.get_z();
}

Vector3D Vector3D::cross(const Vector3D& rhs) const {
    return Vector3D(
        this->get_y() * rhs.get_z() - this->get_z() * rhs.get_y(),
        this->get_z() * rhs.get_x() - this->get_x() * rhs.get_z(),
        this->get_x() * rhs.get_y() - this->get_y() * rhs.get_x()
    );
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "Vector3D { coords[0] = " << vec.get_x() << ", coords[1] = " << vec.get_y()
       << ", coords[2] = " << vec.get_z() << " }";

    return os;
}
