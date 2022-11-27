#ifndef NODE_HPP
#define NODE_HPP

#include "math/Vector3.hpp"

#include <vector>
#include <memory>
#include "rigid_body.hpp"

class Node
{
private:
    math::Vector3 center;
    float half_width;
    std::vector<std::shared_ptr<RigidBody>> object_list;
    std::vector<std::shared_ptr<Node*>> p_child;

public:
    Node(/* args */);
    ~Node();
    
    math::Vector3 get_center();
    float get_half_width();
    std::vector<std::shared_ptr<RigidBody>> get_object_list();
    std::vector<std::shared_ptr<Node*>> get_children();

    void set_center(math::Vector3 center);
    void set_half_width(float half_width);
    void set_object_list(std::vector<std::shared_ptr<RigidBody>> object_list);
    void set_children(std::vector<std::shared_ptr<RigidBody>> children);

    void add_child(Node* child);
};










#endif