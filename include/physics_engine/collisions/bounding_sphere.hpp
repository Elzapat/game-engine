#ifndef BOUNDING_SPHERE_HPP
#define BOUNDING_SPHERE_HPP

#include "math/vector3.hpp"

class BoundingSphere {
    private:
        math::Vector3 center;
        float radius;

    public:
        BoundingSphere(math::Vector3 _center, float _radius);
        BoundingSphere(BoundingSphere first, BoundingSphere second);

        bool overlaps(const BoundingSphere& other) const;
};

#endif // BOUNDING_SPHERE_HPP
