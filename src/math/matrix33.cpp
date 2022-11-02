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

Vector3 Matrix33::get_line(int line) {
    if (line < 0)
        line = 0;
    else if (line > 2)
        line = 2;
        
    Vector3 new_vector(this->values[line], this->values[line + 1], this->values[line + 2]);
    return new_vector;
}

Vector3 Matrix33::get_column(int column) {
    if (column < 0)
        column = 0;
    else if (column > 2)
        column = 2;
        
    Vector3 new_vector(this->values[column], this->values[column + 3], this->values[column + 6]);
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

void Matrix33::set_line(int line, Vector3 vect_line) {
    this->values[line] = vect_line.get_x();
    this->values[line + 1] = vect_line.get_y();
    this->values[line + 2] = vect_line.get_z();
}

void Matrix33::set_column(int column, Vector3 vect_column) {
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

Vector3 Matrix33::operator*(const Vector3& other) const {
    Vector3 new_vector(other.dot(get_line(0)), other.dot(get_line(1)), other.dot(get_line(2)))
    return new_vector;
}


float Matrix33::get_det() {
    float a = this->get_value(0,0);
    float b = this->get_value(0,1);
    float c = this->get_value(0,2);
    float d = this->get_value(1,0);
    float e = this->get_value(1,1);
    float f = this->get_value(1,2);
    float g = this->get_value(2,0);
    float h = this->get_value(2,1);
    float i = this->get_value(2,2);

    return a*e*i + d*h*c + g*b*f - a*h*f - g*e*c - d*b*i;
}

Matrix33 Matrix33::inverse() {

    float det = this->get_det();

    Matrix33 new_matrix33;

    if(det != 0) {
        for(int line = 0; line < 3; line++) {
            for(int column = 0; column < 3; column++) {

               new_matrix33.set_value(column, line,
                    ( this->get_value((line + 1) % 3,(column + 1) % 3)
                    * this->get_value((line + 2) % 3,(column + 2) % 3)
                    - this->get_value((line + 1) % 3,(column + 2) % 3)
                    * this->get_value((line + 2) % 3,(column + 1) % 3) )
                    / det
                );
            }
        }
    }
    //else ???

    return new_matrix33;
}

Matrix33 Matrix33::transpose() {
    Matrix33 new_matrix33;

    for(int line = 0; line < 3; line++) {
        for(int column = 0; column < 3; column++) {
            new_matrix33.set_value(line, column, this->get_value(column,line));
        }
    }

    return new_matrix33;
}

void Matrix33::set_orientation(const Quaternion& q) {
    float w = q.get_value(0);
    float x = q.get_value(1);
    float y = q.get_value(2);
    float z = q.get_value(3);

    this->set_value(0, 0, 1 - 2 * (y ^ 2) - 2 * (z ^ 2));
    this->set_value(1, 1, 1 - 2 * (x ^ 2) - 2 * (z ^ 2));
    this->set_value(2, 2, 1 - 2 * (y ^ 2) - 2 * (x ^ 2));

    this->set_value(0, 1, 2*x*y + 2*z*w);
    this->set_value(0, 2, 2*x*z - 2*y*w);
    this->set_value(1, 0, 2*x*y - 2*z*w);
    this->set_value(1, 2, 2*z*y + 2*x*w);
    this->set_value(2, 0, 2*x*z + 2*y*w);
    this->set_value(2, 1, 2*z*y - 2*x*w);
}