#include "physics_engine/collisions/node.hpp"

Node::Node() {
    this->object_list = std::vector<std::shared_ptr<RigidBody>>();
    this->p_child = std::vector<std::shared_ptr<Node>>();
}

Node::~Node() {}

math::Vector3 Node::get_center() {
    return this->center;
}

float Node::get_half_width() {
    return this->half_width;
}

std::vector<std::shared_ptr<RigidBody>> Node::get_object_list() {
    return this->object_list;
}

std::vector<std::shared_ptr<Node>> Node::get_children() {
    return this->p_child;
}

void Node::set_center(math::Vector3 center) {
    this->center = center;
}

void Node::set_half_width(float half_width) {
    this->half_width = half_width;
}

void Node::set_object_list(std::vector<std::shared_ptr<RigidBody>> object_list) {
    this->object_list = object_list;
}

void Node::set_children(std::vector<std::shared_ptr<Node>> children) {
    this->p_child = children;
}

void Node::add_child(std::shared_ptr<Node> child) {
    this->p_child.push_back(child);
}

void Node::insert_object(std::shared_ptr<RigidBody> object) {
    bool straddle = false;
    int index = 0;

    math::Vector3 delta = object->get_position() - this->center;

    float distance = this->half_width - object->get_bounding_sphere().get_radius();

    if (std::abs(delta.get_x()) > distance) {
        straddle = true;
    } else if (delta.get_x() > 0.0f) {
        index |= (1 << 2);
    }

    if (std::abs(delta.get_y()) > distance) {
        straddle = true;
    } else if (delta.get_y() > 0.0f) {
        index |= (1 << 1);
    }

    if (std::abs(delta.get_z()) > distance) {
        straddle = true;
    } else if (delta.get_z() > 0.0f) {
        index |= (1 << 0);
    }

    if (!straddle && this->p_child[index] != nullptr) {
        this->p_child[index]->insert_object(object);
    } else {
        this->object_list.push_back(object);
    }
}

void Node::reset_objects() {
    this->object_list = std::vector<std::shared_ptr<RigidBody>>();
    for (int i = 0; i < 8; i++) {
        if (p_child[i] != nullptr) {
            this->p_child[i]->reset_objects();
        }
    }
}

void Node::test_all_collisions(
    std::vector<PossibleCollision>* rigid_bodies_list,
    std::vector<std::shared_ptr<Node>> ancestors
) {
    int this_size = this->object_list.size();

    int ancestors_size = ancestors.size();

    //tests ancestors
    for (int i = 0; i < ancestors_size; i++) {
        std::vector<std::shared_ptr<RigidBody>> ancestor_object_list =
            ancestors[i]->get_object_list();
        int ancestor_size = ancestor_object_list.size();

        for (int j = 0; j < ancestor_size; j++) {
            for (int k = 0; k < this_size; k++) {
                if (ancestor_object_list[j] != this->object_list[k]) {
                    PossibleCollision rb_duo;
                    rb_duo.first = ancestor_object_list[j];
                    rb_duo.second = this->object_list[k];
                    rigid_bodies_list->push_back(rb_duo);
                }
            }
        }
    }

    //test brothers
    for (int i = 0; i < this_size; i++) {
        for (int j = this_size - 1; j > i; j--) {
            PossibleCollision rb_duo;
            rb_duo.first = this->object_list[i];
            rb_duo.second = this->object_list[j];
            rigid_bodies_list->push_back(rb_duo);
        }
    }

    ancestors.push_back(std::make_shared<Node>(*this));

    for (int i = 0; i < 8; i++) {
        if (p_child[i] != nullptr) {
            this->p_child[i]->test_all_collisions(rigid_bodies_list, ancestors);
        }
    }
}

std::vector<PossibleCollision> Node::process(std::vector<Object> object_list) {
    this->reset_objects();

    int s = object_list.size();
    for (int i = 0; i < s; i++) {
        this->insert_object(object_list[i].get_rigid_body());
    }

    std::vector<PossibleCollision> list = std::vector<PossibleCollision>();
    this->test_all_collisions(&list, std::vector<std::shared_ptr<Node>>());
    return list;
}

std::shared_ptr<Node> build_octree(math::Vector3 center, float half_width, int stop_depth) {
    if (stop_depth < 0) {
        return nullptr;
    } else {
        std::shared_ptr<Node> pNode = std::make_shared<Node>();
        pNode->set_center(center);
        pNode->set_half_width(half_width);

        math::Vector3 offset;
        float step = half_width * 0.5f;
        for (int i = 0; i < 8; i++) {
            offset.set_x((i & 1) ? step : -step);
            offset.set_y((i & 2) ? step : -step);
            offset.set_z((i & 4) ? step : -step);
            pNode->add_child(build_octree(center + offset, step, stop_depth - 1));
        }
        return pNode;
    }
}
