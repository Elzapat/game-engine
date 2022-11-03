#include "math/matrix4.hpp"

using namespace math;

Vector3 Matrix4::operator*(const Vector3& rhs) const {
    return Vector3(
        rhs.get_x() * this->values[0] + rhs.get_y() * this->values[1]
            + rhs.get_z() * this->values[2] + this->values[3],

        rhs.get_x() * this->values[4] + rhs.get_y() * this->values[5]
            + rhs.get_z() * this->values[6] + this->values[7],

        rhs.get_x() * this->values[8] + rhs.get_y() * this->values[9]
            + rhs.get_z() * this->values[10] + this->values[11]
    );
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const {
    Matrix4 res;

    res.values[0] = rhs.values[0] * this->values[0] + rhs.values[4] * this->values[1]
        + rhs.values[8] * this->values[2];
    res.values[4] = rhs.values[0] * this->values[4] + rhs.values[4] * this->values[5]
        + rhs.values[8] * this->values[6];
    res.values[8] = rhs.values[0] * this->values[8] + rhs.values[4] * this->values[9]
        + rhs.values[8] * this->values[10];

    res.values[1] = rhs.values[1] * this->values[0] + rhs.values[5] * this->values[1]
        + rhs.values[9] * this->values[2];
    res.values[5] = rhs.values[1] * this->values[4] + rhs.values[5] * this->values[5]
        + rhs.values[9] * this->values[6];
    res.values[9] = rhs.values[1] * this->values[8] + rhs.values[5] * this->values[9]
        + rhs.values[9] * this->values[10];

    res.values[2] = rhs.values[2] * this->values[0] + rhs.values[6] * this->values[1]
        + rhs.values[10] * this->values[2];
    res.values[6] = rhs.values[2] * this->values[4] + rhs.values[6] * this->values[5]
        + rhs.values[10] * this->values[6];
    res.values[10] = rhs.values[2] * this->values[8] + rhs.values[6] * this->values[9]
        + rhs.values[10] * this->values[10];

    res.values[3] = rhs.values[3] * this->values[0] + rhs.values[7] * this->values[1]
        + rhs.values[11] * this->values[2] + this->values[3];
    res.values[7] = rhs.values[3] * this->values[4] + rhs.values[7] * this->values[5]
        + rhs.values[11] * this->values[6] + this->values[7];
    res.values[11] = rhs.values[3] * this->values[8] + rhs.values[7] * this->values[9]
        + rhs.values[11] * this->values[10] + this->values[11];

    return res;
}

Matrix4 Matrix4::translate(const Vector3& translation) const {}

Matrix4 Matrix4::rotate(const Vector3& rotation) const {}
