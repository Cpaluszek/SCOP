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

    // Set vertex color
    Vec3f startColor = Vec3f(0.2f, 0.2f, 0.2f);
    Vec3f endColor = Vec3f(0.8f, 0.8f, 0.8f);
    for (size_t i = 0; i < this->vertices.size(); i++) {
        float lerpValue = (i / 3.0f) / (this->vertices.size() / 3.0f);
        // float lerpValue = static_cast<float>(i) / this->vertices.size();
        float r = math::lerp(startColor.x, endColor.x, lerpValue);
        float g = math::lerp(startColor.y, endColor.y, lerpValue);
        float b = math::lerp(startColor.z, endColor.z, lerpValue);
        this->verticesColors.push_back({r, g, b});
    }
}
