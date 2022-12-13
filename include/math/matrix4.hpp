#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "math/vector3.hpp"
#include "math/quaternion.hpp"

namespace math {
    class Matrix4 {
        private:
            std::array<float, 12> values;

        public:
            float determinant() const;
            Matrix4 inverse();

            Matrix4& set_translation(const Vector3& translation);
            Matrix4& set_orientation(const Quaternion& rotation);

            Vector3 operator*(const Vector3& rhs) const;
            Matrix4 operator*(const Matrix4& rhs) const;

            math::Vector3 get_axis_vector(int i) const;

            std::array<float, 12> get_values() const;
            std::array<float, 12>& get_values_ref();
            glm::mat4 to_glm_mat4() const;
    };
}

#endif // MATRIX4_HPP
