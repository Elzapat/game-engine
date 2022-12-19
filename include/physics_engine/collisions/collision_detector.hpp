#ifndef COLLISION_DETECTOR_HPP
#define COLLISION_DETECTOR_HPP

#include <vector>
#include <memory>

#include "math/vector3.hpp"
#include "physics_engine/contacts/rigid_bodies/contact.hpp"
#include "physics_engine/primitives.hpp"

struct CollisionData {
    std::vector<Contact> contacts;
    float friction;
    float restitution;
};

class CollisionDetector {
    public:
        void sphere_sphere(const Sphere& first, const Sphere& second, CollisionData& data);
        void sphere_half_space(const Sphere& sphere, const Plane& plane, CollisionData& data);
        void sphere_plane(const Sphere& sphere, const Plane& plane, CollisionData& data);
        void box_half_space(const Box& box, const Plane& plane, CollisionData& data);
        void box_sphere(const Box& box, const Sphere& sphere, CollisionData& data);
        void box_box(const Box& first, const Box& second, CollisionData& data);

        void check_collision(std::shared_ptr<Primitive> first, std::shared_ptr<Primitive> second, CollisionData& data);

    private:
        static inline float projection_on_axis(const Box& box, const math::Vector3& axis);
        static inline float penetration_on_axis(
            const Box& box1,
            const Box& box2,
            const math::Vector3& axis,
            const math::Vector3& to_center
        );
        static inline bool try_axis(
            const Box& one,
            const Box& two,
            math::Vector3 axis,
            const math::Vector3 to_center,
            unsigned index,
            float& smallestPen,
            unsigned& smallestCase
        );
        static void fill_point_face_box_box(
            const Box& first,
            const Box& second,
            const math::Vector3 to_center,
            CollisionData& data,
            unsigned best,
            float pen
        );
        static inline math::Vector3 contact_point(
            const math::Vector3& first_point,
            const math::Vector3 first_dir,
            float first_size,
            const math::Vector3& second_point,
            const math::Vector3& second_dir,
            float second_size,
            bool use_first
        );
};

#endif  // COLLISION_DETECTOR_HPP
