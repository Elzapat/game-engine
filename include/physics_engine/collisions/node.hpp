#ifndef NODE_HPP
#define NODE_HPP

#include "math/Vector3.hpp"

#include <vector>
#include <memory>
#include "particle.hpp"

class Node
{
private:
    math::Vector3 center;
    float half_width;
    std::vector<std::shared_ptr<Particle>> object_list;
    std::vector<std::shared_ptr<Node>> p_child;

public:
    Node(/* args */);
    ~Node();
    
    math::Vector3 get_center();
    float get_half_width();
    std::vector<std::shared_ptr<Particle>> get_object_list();
    std::vector<std::shared_ptr<Node>> get_children();

    void set_center(math::Vector3 center);
    void set_half_width(float half_width);
    void set_object_list(std::vector<std::shared_ptr<Particle>> object_list);
    void set_children(std::vector<std::shared_ptr<Node>> children);

    void add_child(std::shared_ptr<Node> child);

    void insert_object(std::shared_ptr<Particle> object);
    void reset_objects();

    void test_all_collisions();

    void process(std::vector<std::shared_ptr<Partcile>> object_list);
};

friend shared_ptr<Node> BuildOctree(math::Vector3 center, float half_width, int stop_depth);

#endif