#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>

#include "physics_engine/rigid_body.hpp"
#include "vulkan_renderer/mesh.hpp"

class Object {
    public:
        Object(std::shared_ptr<RigidBody> rb, Mesh m);

        Mesh& get_mesh();
        std::shared_ptr<RigidBody> get_rigid_body();

    private:
        std::shared_ptr<RigidBody> rigid_body;
        Mesh mesh;
};

#endif // OBJECT_HPP
