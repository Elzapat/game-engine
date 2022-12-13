#include "math/matrix4.hpp"

using namespace math;

float Matrix4::determinant() const {
    const std::array<float, 12>& values = this->values;

    return values[8] * values[5] * values[2] + values[4] * values[9] * values[2]
        + values[8] * values[1] * values[6] - values[0] * values[9] * values[6]
        - values[4] * values[1] * values[10] + values[0] * values[5] * values[10];
}

Matrix4 Matrix4::inverse() {
    Matrix4 res(*this);
    float det = this->determinant();

    if (det == 0) {
        return res;
    }

    det = 1.0f / det;
    std::array<float, 12>& values = res.values;

    values[0] = det * (-values[9] * values[6] + values[5] * values[10]);
    values[4] = det * (values[8] * values[6] - values[4] * values[10]);
    values[8] = det * (-values[8] * values[5] + values[4] * values[9]);

    values[1] = det * (values[9] * values[2] - values[1] * values[10]);
    values[5] = det * (-values[8] * values[2] + values[0] * values[10]);
    values[9] = det * (values[8] * values[1] - values[0] * values[9]);

    values[2] = det * (-values[5] * values[2] + values[1] * values[6]);
    values[6] = det * (+values[4] * values[2] - values[0] * values[6]);
    values[10] = det * (-values[4] * values[1] + values[0] * values[5]);

    values[3] = det
        * (values[9] * values[6] * values[3] - values[5] * values[10] * values[3]
           - values[9] * values[2] * values[7] + values[1] * values[10] * values[7]
           + values[5] * values[2] * values[11] - values[1] * values[6] * values[11]);
    values[7] = det
        * (-values[8] * values[6] * values[3] + values[4] * values[10] * values[3]
           + values[8] * values[2] * values[7] - values[0] * values[10] * values[7]
           - values[4] * values[2] * values[11] + values[0] * values[6] * values[11]);
    values[11] = det
        * (values[8] * values[5] * values[3] - values[4] * values[9] * values[3]
           - values[8] * values[1] * values[7] + values[0] * values[9] * values[7]
           + values[4] * values[1] * values[11] - values[0] * values[5] * values[11]);

    return res;
}

Matrix4& Matrix4::set_translation(const Vector3& translation) {
    this->values[3] = translation.get_x();
    this->values[7] = translation.get_y();
    this->values[11] = translation.get_z();

    return *this;
}

Matrix4& Matrix4::set_orientation(const Quaternion& rot) {
    float w = rot.get_w(), x = rot.get_x(), y = rot.get_y(), z = rot.get_z();

    this->values[0] = 1 - (2 * y * y + 2 * z * z);
    this->values[1] = 2 * x * y + 2 * z * w;
    this->values[2] = 2 * x * z - 2 * y * w;

    this->values[4] = 2 * x * y - 2 * z * w;
    this->values[5] = 1 - (2 * x * x + 2 * z * z);
    this->values[6] = 2 * y * z + 2 * x * w;

    this->values[8] = 2 * x * z + 2 * y * w;
    this->values[9] = 2 * y * z - 2 * x * w;
    this->values[10] = 1 - (2 * x * x + 2 * y * y);

    return *this;
}

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

Vector3 Matrix4::get_axis_vector(int i) const {
    return Vector3(this->values[i], this->values[i + 4], this->values[i + 8]);
}

glm::mat4 Matrix4::to_glm_mat4() const {
    float matrix[16];
    std::copy(this->values.data(), this->values.data() + 12, matrix);

    matrix[12] = matrix[13] = matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    return glm::transpose(glm::make_mat4(matrix));
}

std::array<float, 12> Matrix4::get_values() const {
    return this->values;
}

std::array<float, 12>& Matrix4::get_values_ref() {
    return this->values;
}
