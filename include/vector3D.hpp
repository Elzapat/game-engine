#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D {
    private:
        float x, y, z;

    public:
        Vector3D(float x = 0.0, float y = 0.0, float z = 0.0) noexcept;
        ~Vector3D();

        void set_x(float x) noexcept;
        void set_y(float y) noexcept;
        void set_z(float z) noexcept;

        void get_x() const noexcept;
        void get_y() const noexcept;
        void get_z() const noexcept;

        Vector3D operator+(Vector3D rhs) const noexcept;
        Vector3D operator-(Vector3D rhs) const noexcept;
        Vector3D operator*(float rhs) const noexcept;
};

#endif // VECTOR3D_HPP
