#ifndef QUATERNIONS_HPP
#define QUATERNIONS_HPP

#include <cmath>

#include "vector3.hpp"

namespace math {
    class Quaternion {
        private:
            float w, x, y, z;

        public:
            Quaternion(float w = 0.0f, float x = 1.0f, float y = 0.0f, float z = 0.0f);
            Quaternion(float w, const Vector3 vector);

            float get_w() const;
            float get_x() const;
            float get_y() const;
            float get_z() const;

            void set_w(const float w);
            void set_x(const float x);
            void set_y(const float y);
            void set_z(const float z);

            Quaternion normalize();
            Quaternion rotate(const Vector3& rotation);
            void update();

            Quaternion operator*(const Quaternion& rhs) const;
            Quaternion& operator*=(const Quaternion& rhs);
    };
};  // namespace math

#endif  // QUATERNIONS_HPP
