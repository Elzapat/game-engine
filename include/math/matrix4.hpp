#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>

#include "math/vector3.hpp"

namespace math {
    class Matrix4 {
        private:
            std::array<float, 12> values;

        public:
            Vector3 operator*(const Vector3& rhs) const;
            Matrix4 operator*(const Matrix4& rhs) const;

            Matrix4 translate(const Vector3& translation) const;
            Matrix4 rotate(const Vector3& rotation) const;
    };
}

#endif // MATRIX4_HPP
