#include "../../include/math/vector3.hpp"

using namespace math;

Vector3::Vector3(float x, float y, float z) : coords({x, y, z}) {}
Vector3::~Vector3() {}

void Vector3::set_x(const float x) {
    this->coords[0] = x;
}

void Vector3::set_y(const float y) {
    this->coords[1] = y;
}

void Vector3::set_z(const float z) {
    this->coords[2] = z;
}

float Vector3::get_x() const {
    return this->coords[0];
}

float Vector3::get_y() const {
    return this->coords[1];
}

float Vector3::get_z() const {
    return this->coords[2];
}

float Vector3::norm() const {
    return std::sqrt(
        std::pow(this->get_x(), 2) + std::pow(this->get_y(), 2) + std::pow(this->get_z(), 2)
    );
}

Vector3 Vector3::normalize() const {
    float norm = this->norm();

    if (norm == 0.0f) {
        return Vector3();
    }

    return Vector3(this->get_x() / norm, this->get_y() / norm, this->get_z() / norm);
}

Vector3 Vector3::invert() const {
    return Vector3(-this->get_x(), -this->get_y(), -this->get_z());
}

/* void translate(Vector3 const& translation) ; */
/* // TODO: when Quaternions are implemented */
/* // void rotate(Quaternion rotation) ; */
/* void scale(float scale) ; */
/*  */

glm::vec3 Vector3::to_glm_vec3() {
    return glm::vec3(this->get_x(), this->get_y(), this->get_z());
}

float* Vector3::data() {
    return this->coords.data();
}

Vector3 Vector3::operator+(const Vector3& rhs) const {
    return Vector3(
        this->coords[0] + rhs.coords[0],
        this->coords[1] + rhs.coords[1],
        this->coords[2] + rhs.coords[2]
    );
    /* return Vector3(*this) += rhs; */
}

Vector3& Vector3::operator+=(const Vector3& rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const {
    return Vector3(
        this->get_x() - rhs.get_x(),
        this->get_y() - rhs.get_y(),
        this->get_z() - rhs.get_z()
    );
}

Vector3& Vector3::operator-=(const Vector3& rhs) {
    *this = *this - rhs;
    return *this;
}

Vector3 Vector3::operator*(const float& rhs) const {
    Vector3 res = Vector3(*this);

    res.coords[0] *= rhs;
    res.coords[1] *= rhs;
    res.coords[2] *= rhs;

    return res;
}

Vector3& Vector3::operator*=(const float& rhs) {
    this->coords[0] *= rhs;
    this->coords[1] *= rhs;
    this->coords[2] *= rhs;

    return *this;
}

Vector3 Vector3::operator/(const float& rhs) const {
    Vector3 res = Vector3(*this);

    res.coords[0] /= rhs;
    res.coords[1] /= rhs;
    res.coords[2] /= rhs;

    return res;
}

Vector3& Vector3::operator/=(const float& rhs) {
    this->coords[0] /= rhs;
    this->coords[1] /= rhs;
    this->coords[2] /= rhs;

    return *this;
}

Vector3 Vector3::operator-() {
    return this->invert();
}

float Vector3::dot(const Vector3& rhs) const {
    return this->get_x() * rhs.get_x() + this->get_y() * rhs.get_y() + this->get_z() * rhs.get_z();
}

Vector3 Vector3::cross(const Vector3& rhs) const {
    return Vector3(
        this->get_y() * rhs.get_z() - this->get_z() * rhs.get_y(),
        this->get_z() * rhs.get_x() - this->get_x() * rhs.get_z(),
        this->get_x() * rhs.get_y() - this->get_y() * rhs.get_x()
    );
}

// clang-format off
namespace math {
    std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "Vector3 { x = " << vec.get_x() << ", y = " << vec.get_y()
            << ", y = " << vec.get_z() << " }";

        return os;
    }

    Vector3 operator*(float lhs, const math::Vector3& rhs) {
        return rhs * lhs;
    }
}
