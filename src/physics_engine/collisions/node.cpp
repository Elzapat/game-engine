#include "physics_engine/collisions/node.hpp"

Node::Node() {
    this->object_list = std::vector<std::shared_ptr<RigidBody>>();
    this->p_child = std::vector<std::shared_ptr<Node*>>();
}

Node::~Node() {}

math::Vector3 get_center() {
    return this->center;
}

float get_half_width() {
    return this->half_with;
}

std::vector<std::shared_ptr<RigidBody>> Node::get_object_list() {
    return this->object_list;
}

std::vector<std::shared_ptr<Node*>> Node::get_children() {
    return this->p_child;
}


void Node::set_center(math::Vector3 center) {
    this->center = center;
}

void Node::set_half_width(float half_width) {
    this->half_with = half_width;
}

void Node::set_object_list(std::vector<std::shared_ptr<RigidBody>> object_list) {
    this->object_list = object_list;
}

void Node::set_children(std::vector<std::shared_ptr<RigidBody>> children) {
    this->p_child = children;
}


void Node::add_child(Node* child) {
    this->p_child.push_back(child);
}


friend Node* BuildOctree(math::Vector3 center, float half_width, int stop_depth) {
    if (stop_depth < 0) {
        return NULL;
    } else {
        Node *pNode = new Node;
        pNode->set_center(center);
        pNode->set_half_width(half_width)

        math::Vector3 offset;
        float step = half_width * 0.5f;
        for (int i = 0; i < 8; i++) {
            offset.set_x((i & 1) ? step : -step);
            offset.set_y((i & 2) ? step : -step);
            offset.set_z((i & 4) ? step : -step);
            pNode->add_child(BuildOctree(center + offset, step, stop_depth - 1));
        }
        return pNode;
    }
}

