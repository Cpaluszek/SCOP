#include <utility>

#include "Mesh.h"
#include "math.h"
#include "settings.h"

Mesh::Mesh(VertexVector& vertices): vertices(std::move(vertices))
{
    // this->mapTextureCoordinates();
    this->computeObjectPosition();
    this->setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
}

// Todo: set function as const - move rotation
void Mesh::draw(Shader& shader, const float deltaTime) {
    const Mat4f identity(1.0f);

    Mat4f model = Mat4f::translate(identity, this->position);
    model = Mat4f::translate(model, this->origin);

    // this->rotation.x += math::radians(2.0f * deltaTime);
    this->rotation.y += math::radians(20.0f * deltaTime);
    // this->rotation.z -= math::radians(6.0f * deltaTime);
    // model = Mat4f::rotate(model, this->rotation.x, Vec3f(1.0f, 1.0f, 0.0f));
    model = Mat4f::rotate(model, this->rotation.y, Vec3f(0.0f, 1.0f, 0.0f));
    // model = Mat4f::rotate(model, this->rotation.z, Vec3f(0.0f, 0.0f, 1.0f));
    model = Mat4f::translate(model, this->origin.scale(-1.0f));
    model = Mat4f::transpose(model);
    shader.setMat4("model", model);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    glBindVertexArray(0);
}

void Mesh::resetTransform() {
    this->position = this->origin.scale(-1.0f);
    this->rotation = Vec3f();
}

void Mesh::setupMesh() {
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
    // vertex normal
    // Todo: normals

    // vertex color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(9 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

void Mesh::mapTextureCoordinates() {
    // Todo: find a proper way to manage uv mapping
    for (auto &vertex: this->vertices) {

        float theta = std::atan2(vertex.position.z, vertex.position.x);
        float phi = std::acos(vertex.position.y / vertex.position.length());
        vertex.textX = (theta + M_PI) / (2.0f * M_PI);
        vertex.textY = phi / M_PI;
    }
}

void Mesh::computeObjectPosition() {
    Vec3f range = this->vertices.at(0).position;
    Vec3f sum;
    for (Vertex v: this->vertices) {
        sum += v.position;

        if (v.position.x > range.x) {
            range.x = fabs(v.position.x);
        }
        if (v.position.y > range.y) {
            range.y = fabs(v.position.y);
        }
        if (v.position.z > range.z) {
            range.z = fabs(v.position.z);
        }
    }
    this->origin = sum.scale(1.0f / this->vertices.size());

    this->position = this->origin.scale(-1.0f);
    range -= this->origin;
    float max = range.x;
    if (range.y > max) {
        max = range.y;
    }
    if (range.z > max) {
        max = range.z;
    }
    if (max > CAM_START_POSITION.z) {
        this->position.z -= max * 2.0f + CAM_START_POSITION.z;
    }
}

