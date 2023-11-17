#include "../inc/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices):
    vertices(vertices),
    indices(indices)
{
    this->computVerticesColors();
    this->setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    // glDeleteBuffers(1, &this->ebo);
}

void Mesh::draw(Shader& shader, const double currentTime) const {
    const Vec3f position(0.0f, 0.0f, -5.0f);
    const Mat4f identity(1.0f);   // Note: store idenity as const?
    Mat4f model = Mat4f::translate(identity, position);

    const GLfloat angle = math::radians(currentTime * 30.0f);
    model = Mat4f::rotate(model, angle, Vec3f(0.0f, 1.0f, 0.0f));
    model = Mat4f::transpose(model);
    shader.setMat4("model", model);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    // glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    // Todo: check for errors
    glGenVertexArrays(1, &this->vao); 
    glGenBuffers(1, &this->vbo);
    // glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(
            GL_ARRAY_BUFFER,
            this->vertices.size() * sizeof(Vertex),
            this->vertices.data(),
            GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    // glBufferData(
    //         GL_ELEMENT_ARRAY_BUFFER,
    //         this->indices.size() * sizeof(unsigned int),
    //         this->indices.data(),
    //         GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    // vertex colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    // vertex texture coords
    
    glBindVertexArray(0);
}

void Mesh::computVerticesColors() {
    if (this->vertices.size() == 0) {
        return ;
    }

    Vec3f startColor = Vec3f(0.3f, 0.3f, 0.3f);
    Vec3f endColor = Vec3f(0.9f, 0.9f, 0.9f);
    float triangleCount = this->vertices.size() / 3.0f;

    for (size_t i = 0; i < this->vertices.size(); i++) {
        float lerpValue = (i / 3.0f) / triangleCount;

        this->vertices[i].r = math::lerp(startColor.x, endColor.x, lerpValue);
        this->vertices[i].g = math::lerp(startColor.y, endColor.y, lerpValue);
        this->vertices[i].b = math::lerp(startColor.z, endColor.z, lerpValue);
    }
}
