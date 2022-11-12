#include "vulkan_renderer/mesh.hpp"

#if defined(_MSC_VER)
    #include <corecrt_math_defines.h>
#endif

Mesh::Mesh(MeshType _type, std::vector<Vertex> _vertices, std::vector<uint32_t> _indices) :
    vertices(_vertices),
    indices(_indices),
    type(_type)  //
{}

Mesh::~Mesh() {}

Mesh Mesh::sphere(float radius, int sectors, int stacks) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    float x, y, z, xy;
    float nx, ny, nz, length_inv = 1.0f / radius;
    float sector_step = 2.0f * M_PI / static_cast<float>(sectors);
    float stack_step = M_PI / static_cast<float>(stacks);
    float sector_angle, stack_angle;

    for (int i = 0; i <= stacks; i++) {
        stack_angle = M_PI / 2.0f - static_cast<float>(i) * stack_step;
        xy = radius * std::cos(stack_angle);
        z = radius * std::sin(stack_angle);

        for (int j = 0; j <= sectors; j++) {
            sector_angle = static_cast<float>(j) * sector_step;

            x = xy * std::cos(sector_angle);
            y = xy * std::sin(sector_angle);

            nx = x * length_inv;
            ny = y * length_inv;
            nz = z * length_inv;

            Vertex vertex = {{x, y, z}, {1.0f, 1.0f, 0.0f}, {nx, ny, nz}};
            vertices.push_back(vertex);
        }
    }

    int k1, k2;

    for (int i = 0; i < stacks; i++) {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; j++, k1++, k2++) {
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k1);

            indices.push_back(k2 + 1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);
        }
    }

    return Mesh(MeshType::Sphere, std::move(vertices), std::move(indices));
}

Mesh Mesh::cube() {
    std::vector<Vertex> vertices = {
        // Bottom
        {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

        // Top
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},

        // Right
        {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

        // Left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},

        // Back
        {{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

        // Front
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
    };

    // clang-format off
    std::vector<uint32_t> indices = {
        // Bottom
        2, 1, 0, 0, 3, 2,
        // Top
        4, 5, 6, 6, 7, 4,
        // Right
        10, 9, 8, 8, 11, 10,
        // Left
        14, 13, 12, 12, 15, 14,
        // Back
        18, 17, 16, 16, 19, 18,
        // Front
        22, 21, 20, 20, 23, 22

    };

    return Mesh(MeshType::Cube, std::move(vertices), std::move(indices));
}
