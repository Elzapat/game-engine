#include "../../include/math/matrix33.hpp"

using namespace math;

Matrix33::Matrix33(
    float x1 = 0.0, float y1 = 0.0, float z1 =0.0,
    float x2 = 0.0, float y2 = 0.0, float z2 =0.0,
    float x3 = 0.0, float y3 = 0.0, float z3 =0.0   
) {
    this->values = {x1, y1, z1, x2, y2, z2, x3, y3, z3};
}

Matrix33::~Matrix33() {}

//getters
std::array<float, 9> Matrix33::get_values() {
    return this->values;
}

Vector3D Matrix33::get_line(int line) {
    if (line < 0)
        line = 0;
    else if (line > 2)
        line = 2;
        
    Vector3D new_vector(this->values[line], this->values[line + 1], this->values[line + 2]);
    return new_vector;
}

Vector3D Matrix33::get_column(int column) {
    if (column < 0)
        column = 0;
    else if (column > 2)
        column = 2;
        
    Vector3D new_vector(this->values[column], this->values[column + 3], this->values[column + 6]);
    return new_vector;
}

float Matrix33::get_value(int line, int column) {
    return this->values[line * 3 + column];
}

//setters
void Matrix33::set_value(int line, int column, float value) {
    this->values[line * 3 + column] = value;
}

void Matrix33::set_values(std::array<float, 9> values) {
    this->values = values;
}

void Matrix33::set_line(int line, Vector3D vect_line) {
    this->values[line] = vect_line.get_x();
    this->values[line + 1] = vect_line.get_y();
    this->values[line + 2] = vect_line.get_z();
}

void Matrix33::set_column(int column, Vector3D vect_column) {
    this->values[column] = vect_line.get_x();
    this->values[column + 3] = vect_line.get_y();
    this->values[column + 6] = vect_line.get_z();
}


Matrix33 Matrix33::operator*(const Matrix33& other) const {
    Matrix33 new_matrix33();

    for(int i = 0; i < 3; i++) {
        new_matrix33->set_column(i, this * other->get_column(i));
    }

    return new_matrix33;
}

Vector3D Matrix33::operator*(const Vector3D& other) const {
    Vector3D new_vector(other.dot(get_line(0)), other.dot(get_line(1)), other.dot(get_line(2)))
    return new_vector;
}
