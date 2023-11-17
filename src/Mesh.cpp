#include "../inc/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices):
    vertices(vertices)
{
    this->setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
}

void Mesh::draw(Shader& shader, const double currentTime) const {
    const Vec3f position(0.0f, 0.0f, -5.0f);
    const Mat4f identity(1.0f);   // Note: store idenity as const?
    Mat4f model = Mat4f::translate(identity, position);

    const GLfloat angle = math::radians(currentTime * 20.0f);
    model = Mat4f::rotate(model, angle, Vec3f(0.0f, 1.0f, 0.0f));
    model = Mat4f::transpose(model);
    shader.setMat4("model", model);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    // Todo: check for errors
    glGenVertexArrays(1, &this->vao); 
    glGenBuffers(1, &this->vbo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(
            GL_ARRAY_BUFFER,
            this->vertices.size() * sizeof(Vertex),
            this->vertices.data(),
            GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    // vertex colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    // vertex texture coords
    
    glBindVertexArray(0);
}

