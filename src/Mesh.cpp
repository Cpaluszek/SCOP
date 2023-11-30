#include "Mesh.h"

Mesh::Mesh(VertexVector& vertices, Vertex_Format& format): vertices(std::move(vertices)), format(format) {
    this->computeObjectPosition();
   
    if (this->format == VERTEX || this->format == VERTEX_NORMAL) {
        // Note: set program option to pick UVmapping method
        // this->sphericalUVMapping();
        this->cubicUVMapping();
    }

    this->setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
}

void Mesh::draw(Shader& shader) const {
    const Mat4f identity(1.0f);

    Mat4f model = Mat4f::translate(identity, this->position);
    model = Mat4f::translate(model, this->origin);

    model = Mat4f::rotate(model, this->rotation.x, Vec3f(1.0f, 0.0f, 0.0f));
    model = Mat4f::rotate(model, this->rotation.y, Vec3f(0.0f, 1.0f, 0.0f));
    model = Mat4f::rotate(model, this->rotation.z, Vec3f(0.0f, 0.0f, 1.0f));

    model = Mat4f::translate(model, this->origin.scale(-1.0f));
    model = Mat4f::transpose(model);
    shader.setMat4("model", model);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    glBindVertexArray(0);
}

void Mesh::resetTransform() {
    this->position = this->initialPosition;
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

// The mapping functions assume that the the vertices are correctly ordered
// each group of 3 vertices forms a triangle
void Mesh::sphericalUVMapping() {
    for (auto &vertex: this->vertices) {
        float theta = std::atan2(vertex.position.z, vertex.position.x);
        float phi = std::acos(vertex.position.y / vertex.position.length());
        vertex.textX = (theta + M_PI) / (2.0f * M_PI);
        vertex.textY = phi / M_PI;
    }
}

void Mesh::cubicUVMapping() {
    for (size_t i = 0; i < this->vertices.size(); i+=3) {
        Vertex& a = this->vertices.at(i);
        Vertex& b = this->vertices.at(i + 1);
        Vertex& c = this->vertices.at(i + 2);
        Vec3f side1 = b.position - a.position;
        Vec3f side2 = c.position - a.position;

        Vec3f n = Vec3f::cross(side1, side2);
        n = Vec3f::normalize(n);
        n = Vec3f(fabs(n.x), fabs(n.y), fabs(n.z));

        if (n.x >= n.y && n.x >= n.z) {
            a.textX = a.position.z;
            a.textY = a.position.y;
            b.textX = b.position.z;
            b.textY = b.position.y;
            c.textX = c.position.z;
            c.textY = c.position.y;
        } else if (n.y >= n.x && n.y >= n.z) {
            a.textX = a.position.x;
            a.textY = a.position.z;
            b.textX = b.position.x;
            b.textY = b.position.z;
            c.textX = c.position.x;
            c.textY = c.position.z;
        } else if (n.z >= n.x && n.z >= n.y) {
            a.textX = a.position.x;
            a.textY = a.position.y;
            b.textX = b.position.x;
            b.textY = b.position.y;
            c.textX = c.position.x;
            c.textY = c.position.y;
        }
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

    this->initialPosition = this->position;
}

