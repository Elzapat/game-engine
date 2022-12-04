#include "physics_engine/collisions/node.hpp"
#include "stdlib.h"

Node::Node() {
    this->object_list = std::vector<std::shared_ptr<Particle>>();
    this->p_child = std::vector<std::shared_ptr<Node>>();
}

Node::~Node() {}

math::Vector3 get_center() {
    return this->center;
}

float get_half_width() {
    return this->half_with;
}

std::vector<std::shared_ptr<Particle>> Node::get_object_list() {
    return this->object_list;
}

std::vector<std::shared_ptr<Node>> Node::get_children() {
    return this->p_child;
}


void Node::set_center(math::Vector3 center) {
    this->center = center;
}

void Node::set_half_width(float half_width) {
    this->half_with = half_width;
}

void Node::set_object_list(std::vector<std::shared_ptr<Particle>> object_list) {
    this->object_list = object_list;
}

void Node::set_children(std::vector<std::shared_ptr<Particle>> children) {
    this->p_child = children;
}


void Node::add_child(shared_ptr<Node> child) {
    this->p_child.push_back(child);
}

void Node::insert_object(std::shared_ptr<Particle> object) {
    bool straddle = false;
    int index = 0;

    math::Vector3 delta = object->getPosition - this->center;

    float distance = this->half_width + pObject->get_radius();

    if (abs(delta.get_x()) < distance) {
        straddle = true;
    } else if(delta.get_x() > 0.0f) {
        index |= (1 << 2);
    }

    if (abs(delta.get_y()) < distance) {
        straddle = true;
    } else if(delta.get_y() > 0.0f) {
        index |= (1 << 1);
    }

    if (abs(delta.get_z()) < distance) {
        straddle = true;
    } else if(delta.get_z() > 0.0f) {
        index |= (1 << 0);
    }

    if (!straddle && this->p_child[index] != NULL) {
        this->p_child[index]->insert_object(object);
    } else {
        this->object_list->push_back(object);
    }

}

void Node::reset_objects() {
    this->object_list = std::vector<std::shared_ptr<Particle>>();
    for(int i = 0; i < 8; i++) {
        this->pChild[i]->reset_objects();
    }
}

void Node::test_all_collisions(std::vector<std::shared_ptr<Node>> ancestors = std::vector<std::shared_ptr<Node>>()) {
    
    ancestors.push_back(this);
    int ancestors_size = ancestors.size();
    
    for(int i = 0; i < ancestors_size; i++) {
        std::shared_ptr<Particle> ancestor_object_list = ancestors[i]->get_object_list();
        int ancestor_size = ancestor_object_list.size();

        for(int j = 0; j < ancestor_size; j++) {
            int this_size = this->object_list.size();

            for(int k = 0; k < this_size; k++) {
                if(ancestor_object_list[j] != this->object_list[i]) {
                    // tester collision 
                }
            }
        }
    }

    for(int i = 0; i < 8; i++) {
        this->pChild[i]->test_all_collisions(ancestors);
    }
    
}


void Node::process(std::vector<std::shared_ptr<Particle>> object_list) {
    int s = object_list.size();

    for(int i = 0; i < s; i++) {
        this->reset_objects();
        this->insert_object(object_list[i]);
        this->test_all_collisions();
    }
}


friend std::shared_ptr<Node> BuildOctree(math::Vector3 center, float half_width, int stop_depth) {
    if (stop_depth < 0) {
        return NULL;
    } else {
        std::shared_ptr<Node> = new Node;
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

