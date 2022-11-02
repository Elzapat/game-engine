#include "../../include/math/matrix3.hpp"

using namespace math;

Matrix3::Matrix3(
    float x1,
    float y1,
    float z1,
    float x2,
    float y2,
    float z2,
    float x3,
    float y3,
    float z3
) {
    this->values = {x1, y1, z1, x2, y2, z2, x3, y3, z3};
}

Matrix3::~Matrix3() {}

//getters
std::array<float, 9> Matrix3::get_values() {
    return this->values;
}

Vector3 Matrix3::get_line(int line) const {
    std::clamp(line, 0, 2);

    Vector3 new_vector(this->values[line], this->values[line + 1], this->values[line + 2]);
    return new_vector;
}

Vector3 Matrix3::get_column(int column) const {
    std::clamp(column, 0, 2);

    Vector3 new_vector(this->values[column], this->values[column + 3], this->values[column + 6]);
    return new_vector;
}

float Matrix3::get_value(const int line, const int column) const {
    return this->values[line * 3 + column];
}

//setters
void Matrix3::set_value(int line, int column, float value) {
    this->values[line * 3 + column] = value;
}

void Matrix3::set_values(std::array<float, 9> values) {
    this->values = values;
}

void Matrix3::set_line(int line, Vector3 vect_line) {
    this->values[line] = vect_line.get_x();
    this->values[line + 1] = vect_line.get_y();
    this->values[line + 2] = vect_line.get_z();
}

void Matrix3::set_column(int column, Vector3 vect_column) {
    this->values[column] = vect_column.get_x();
    this->values[column + 3] = vect_column.get_y();
    this->values[column + 6] = vect_column.get_z();
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 new_matrix3;

    for (int i = 0; i < 3; i++) {
        new_matrix3.set_column(i, *this * other.get_column(i));
    }

    return new_matrix3;
}

Vector3 Matrix3::operator*(const Vector3& other) const {
    Vector3 new_vector(
        other.dot(this->get_line(0)),
        other.dot(this->get_line(1)),
        other.dot(this->get_line(2))

    );
    return new_vector;
}

float Matrix3::get_det() {
    float a = this->get_value(0, 0);
    float b = this->get_value(0, 1);
    float c = this->get_value(0, 2);
    float d = this->get_value(1, 0);
    float e = this->get_value(1, 1);
    float f = this->get_value(1, 2);
    float g = this->get_value(2, 0);
    float h = this->get_value(2, 1);
    float i = this->get_value(2, 2);

    return a * e * i + d * h * c + g * b * f - a * h * f - g * e * c - d * b * i;
}

Matrix3 Matrix3::inverse() {
    float det = this->get_det();

    Matrix3 new_matrix3;

    if (det != 0) {
        for (int line = 0; line < 3; line++) {
            for (int column = 0; column < 3; column++) {
                new_matrix3.set_value(
                    column,
                    line,
                    (this->get_value((line + 1) % 3, (column + 1) % 3)
                         * this->get_value((line + 2) % 3, (column + 2) % 3)
                     - this->get_value((line + 1) % 3, (column + 2) % 3)
                         * this->get_value((line + 2) % 3, (column + 1) % 3))
                        / det
                );
            }
        }
    }
    //else ???

    return new_matrix3;
}

Matrix3 Matrix3::transpose() {
    Matrix3 new_matrix3;

    for (int line = 0; line < 3; line++) {
        for (int column = 0; column < 3; column++) {
            new_matrix3.set_value(line, column, this->get_value(column, line));
        }
    }

    return new_matrix3;
}

void Matrix3::set_orientation(const Quaternion& q) {
    float w = q.get_w();
    float x = q.get_x();
    float y = q.get_y();
    float z = q.get_z();

    this->set_value(0, 0, 1 - 2 * (y * y) - 2 * (z * z));
    this->set_value(1, 1, 1 - 2 * (x * x) - 2 * (z * z));
    this->set_value(2, 2, 1 - 2 * (y * y) - 2 * (x * x));

    this->set_value(0, 1, 2 * x * y + 2 * z * w);
    this->set_value(0, 2, 2 * x * z - 2 * y * w);
    this->set_value(1, 0, 2 * x * y - 2 * z * w);
    this->set_value(1, 2, 2 * z * y + 2 * x * w);
    this->set_value(2, 0, 2 * x * z + 2 * y * w);
    this->set_value(2, 1, 2 * z * y - 2 * x * w);
}
