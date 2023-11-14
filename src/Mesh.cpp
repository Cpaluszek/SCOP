#include "../inc/Mesh.h"

Mesh::Mesh(Vec3f position): position(position) {
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    //
    // this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    //
    // this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    //
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    //
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f, -0.5f});
    // this->vertices.push_back({0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({-0.5f, -0.5f,  0.5f});
    // this->vertices.push_back({-0.5f, -0.5f, -0.5f});
    //
    // this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({0.5f,  0.5f, -0.5f});
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({-0.5f,  0.5f,  0.5f});
    // this->vertices.push_back({-0.5f,  0.5f, -0.5f});
    // 
    // this->computeVertexColor();
}

void Mesh::setVertices(std::vector<Vertex> const& vertices) {
    this->vertices = vertices;
    this->computeVertexColor();
}

void Mesh::setIndices(std::vector<unsigned int> const& indices) {
    this->indices = indices;
}

void Mesh::computeVertexColor() {
    Vec3f startColor = Vec3f(0.4f, 0.4f, 0.4f);
    Vec3f endColor = Vec3f(1.0f, 1.0f, 1.0f);
    for (size_t i = 0; i < this->vertices.size(); i++) {
        float lerpValue = (i / 3.0f) / (this->vertices.size() / 3.0f);

        float r = math::lerp(startColor.x, endColor.x, lerpValue);
        float g = math::lerp(startColor.y, endColor.y, lerpValue);
        float b = math::lerp(startColor.z, endColor.z, lerpValue);
        this->verticesColors.push_back({r, g, b});
    }
}

