#include "../inc/Mesh.h"

Mesh::Mesh() {};

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    std::cout << "new mesh: vertex count = " << this->vertices.size() << std::endl;

    this->setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
}

void Mesh::setupMesh() {
    // Todo: check for errors
    glGenVertexArrays(1, &this->vao); 
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(
            GL_ARRAY_BUFFER,
            this->vertices.size() * sizeof(Vertex),
            this->vertices.data(),
            GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            this->indices.size() * sizeof(unsigned int),
            this->indices.data(),
            GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    // vertex normals
    // vertex texture coords
    
    glBindVertexArray(0);

    std::cout << "Buffer created" << std::endl;
    std::cout << "glGetError: " << glGetError() << std::endl;
    std::cout << "vao: " << vao << std::endl;
    std::cout << "vbo: " << vbo << std::endl;
    std::cout << "ebo: " << ebo << std::endl;
}

void Mesh::draw(Shader& shader, double currentTime) const {
    std::cout << "shader addr: " << &shader << std::endl;
    Vec3f position;
    Mat4f identity(1.0f);
    Mat4f model = Mat4f::translate(identity, position);

    float angle = math::radians(30.0f * currentTime);
    model = Mat4f::rotate(model, angle, Vec3f(0.0f, 1.0f, 0.0f));
    model = Mat4f::transpose(model);
    shader.setMat4("model", model);
    std::cout << "model: " << model << std::endl;

    std::cout << "glGetError: " << glGetError() << std::endl;
    std::cout << "vao: " << this->vao << std::endl;
    glBindVertexArray(this->vao);
    std::cout << "glGetError: " << glGetError() << std::endl;
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// void Mesh::computeVertexColor() {
//     Vec3f startColor = Vec3f(0.4f, 0.4f, 0.4f);
//     Vec3f endColor = Vec3f(1.0f, 1.0f, 1.0f);
//     for (size_t i = 0; i < this->vertices.size(); i++) {
//         float lerpValue = (i / 3.0f) / (this->vertices.size() / 3.0f);
//
//         float r = math::lerp(startColor.x, endColor.x, lerpValue);
//         float g = math::lerp(startColor.y, endColor.y, lerpValue);
//         float b = math::lerp(startColor.z, endColor.z, lerpValue);
//         this->verticesColors.push_back({r, g, b});
//     }
// }

