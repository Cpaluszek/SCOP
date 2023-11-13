#include "../inc/Mesh.h"

Mesh::Mesh(Vec3f position): position(position) {
    this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f,  0.5f, -0.5f});
    this->vertices.push_back({0.5f,  0.5f, -0.5f});
    this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    this->vertices.push_back({-0.5f, -0.5f, -0.5f});

    this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    this->vertices.push_back({0.5f, -0.5f,  0.5f});
    this->vertices.push_back({0.5f,  0.5f,  0.5f});
    this->vertices.push_back({0.5f,  0.5f,  0.5f});
    this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    this->vertices.push_back({-0.5f, -0.5f,  0.5f});

    this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    this->vertices.push_back({-0.5f,  0.5f,  0.5f});

    this->vertices.push_back({0.5f,  0.5f,  0.5f});
    this->vertices.push_back({0.5f,  0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f,  0.5f});
    this->vertices.push_back({0.5f,  0.5f,  0.5f});

    this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f, -0.5f});
    this->vertices.push_back({0.5f, -0.5f,  0.5f});
    this->vertices.push_back({0.5f, -0.5f,  0.5f});
    this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    this->vertices.push_back({-0.5f, -0.5f, -0.5f});

    this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    this->vertices.push_back({0.5f,  0.5f, -0.5f});
    this->vertices.push_back({0.5f,  0.5f,  0.5f});
    this->vertices.push_back({0.5f,  0.5f,  0.5f});
    this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    this->vertices.push_back({-0.5f,  0.5f, -0.5f});
}
