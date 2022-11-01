#include "../../../include/vulkan_renderer/mesh/sphere.hpp"

Sphere::Sphere(float _radius, int _sectors, int _stacks) :
    radius(_radius),
    sectors(_sectors),
    stacks(_stacks)  //
{
    float x, y, z, xy;  // vertex position

    float sector_step = 2.0f * M_PI / static_cast<float>(this->sectors);
    float stack_step = M_PI / static_cast<float>(this->stacks);
    float sector_angle, stack_angle;

    for (int i = 0; i <= this->stacks; i++) {
        stack_angle = M_PI / 2.0f - static_cast<float>(i) * stack_step;
        xy = radius * std::cos(stack_angle);
        z = radius * std::sin(stack_angle);

        for (int j = 0; j <= this->sectors; j++) {
            sector_angle = static_cast<float>(j) * sector_step;

            x = xy * std::cos(sector_angle);
            y = xy * std::sin(sector_angle);

            Vertex vertex = {{x, y, z}, {1.0f, 1.0f, 0.0f}};
            this->vertices.push_back(vertex);
        }
    }

    /*
    for (uint32_t i = 0; i < this->stacks; i++) {
        uint32_t k1 = i * (static_cast<uint32_t>(this->sectors) + 1);
        uint32_t k2 = k1 + static_cast<uint32_t>(this->sectors) + 1;

        for (uint32_t j = 0; j < this->sectors; j++, k1++, k2++) {
            if (i != 0) {
                this->indices.push_back(k1 + 1);
                this->indices.push_back(k2);
                this->indices.push_back(k1);
            }

            if (i != this->stacks - 1) {
                this->indices.push_back(k2 + 1);
                this->indices.push_back(k2);
                this->indices.push_back(k1 + 1);
            }
        }
    }
    */
    int k1, k2;

    for (int i = 0; i < this->stacks; i++) {
        k1 = i * (this->sectors + 1);
        k2 = k1 + this->sectors + 1;

        for (int j = 0; j < this->sectors; j++, k1++, k2++) {
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k1);

            indices.push_back(k2 + 1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);
        }
    }

    /*
    for (int i = 0; i < sectors * stacks + sectors; i++) {
        indices.push_back(static_cast<uint32_t>(i));
        indices.push_back(static_cast<uint32_t>(i + sectors + 1));
        indices.push_back(static_cast<uint32_t>(i + sectors));

        indices.push_back(static_cast<uint32_t>(i + sectors + 1));
        indices.push_back(static_cast<uint32_t>(i));
        indices.push_back(static_cast<uint32_t>(i + 1));
    }
    */
}

/*
std::vector<Vertex> Sphere::get_vertices() {
    std::vector<Vertex> vertices;

    float x, y, z, xy;  // vertex position

    float sector_step = 2.0f * M_PI / static_cast<float>(SLICES);
    float stack_step = M_PI / static_cast<float>(STACKS);
    float sector_angle, stack_angle;

    for (int i = 0; i <= SLICES; i++) {
        stack_angle = M_PI / 2.0f - static_cast<float>(i) * stack_step;
        xy = SPHERE_RADIUS * std::cos(stack_angle);
        z = SPHERE_RADIUS * std::sin(stack_angle);

        for (int j = 0; j <= SLICES; j++) {
            sector_angle = static_cast<float>(j) * sector_step;

            x = xy * std::cos(sector_angle);
            y = xy * std::sin(sector_angle);

            Vertex vertex = {{x, y, z}, {1.0f, 1.0f, 0.0f}};
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i <= STACKS; i++) {
        float v = static_cast<float>(i) / static_cast<float>(STACKS);
        float phi = v * M_PI;

        for (int j = 0; j <= SLICES; j++) {
            float u = static_cast<float>(j) / static_cast<float>(SLICES);
            float theta = u * (M_PI * 2);

            float x = std::cos(theta) * std::sin(phi);
            float y = std::cos(phi);
            float z = std::sin(theta) * std::cos(phi);

            Vertex vertex = {{x, y, z}, {1.0f, 1.0f, 0.0f}};
            vertices.push_back(vertex);
        }
    }

    std::cout << vertices.size() << std::endl;
    */

/*
    const int RESOLUTION = 8;

    for (int u = 0; u < RESOLUTION; u++) {
        float x = std::sin(M_PI * u);
        float y = 0.0f;
        float z = std::cos(M_PI * u);

        Vertex vertex = {{x, y, z}, {1.0f, 1.0f, 0.0f}};
        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<uint32_t> Sphere::get_indices() {
    std::vector<uint32_t> indices;

    uint32_t k1, k2;

    for (uint32_t i = 0; i < STACKS; i++) {
        k1 = i * (SLICES + 1);
        k2 = k1 + SLICES + 1;

        for (uint32_t j = 0; j < SLICES; j++, k1++, k2++) {
            if (i != 0) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k1);
            }

            if (i != (STACKS - 1)) {
                indices.push_back(k2 + 1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
        }
    }

    for (int i = 0; i < SLICES * STACKS + SLICES; i++) {
        indices.push_back(static_cast<uint32_t>(i));
        indices.push_back(static_cast<uint32_t>(i + SLICES + 1));
        indices.push_back(static_cast<uint32_t>(i + SLICES));

        indices.push_back(static_cast<uint32_t>(i + SLICES + 1));
        indices.push_back(static_cast<uint32_t>(i));
        indices.push_back(static_cast<uint32_t>(i + 1));
    }

    for (int i = 0; i < 8; i++) {
        indices.push_back(i);
    }

    return indices;
}
*/
