#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>
#include <cstdlib>

#include "math/vector3.hpp"
#include "object.hpp"
#include "physics_engine/rigid_body.hpp"

struct PossibleCollision {
    std::shared_ptr<RigidBody> first;
    std::shared_ptr<RigidBody> second;
};

class Node {
    private:
        math::Vector3 center;
        float half_width;
        std::vector<std::shared_ptr<RigidBody>> object_list;
        std::vector<std::shared_ptr<Node>> p_child;

    public:
        Node();
        ~Node();

        math::Vector3 get_center();
        float get_half_width();
        std::vector<std::shared_ptr<RigidBody>> get_object_list();
        std::vector<std::shared_ptr<Node>> get_children();

        void set_center(math::Vector3 center);
        void set_half_width(float half_width);
        void set_object_list(std::vector<std::shared_ptr<RigidBody>> object_list);
        void set_children(std::vector<std::shared_ptr<Node>> children);

        void add_child(std::shared_ptr<Node> child);

        void insert_object(std::shared_ptr<RigidBody> object);
        void reset_objects();

        void test_all_collisions(
            std::vector<PossibleCollision>* rigid_bodies_list,
            std::vector<std::shared_ptr<Node>> ancestors
        );

        std::vector<PossibleCollision> process(std::vector<Object> object_list);
};

std::shared_ptr<Node> build_octree(math::Vector3 center, float half_width, int stop_depth);

#endif