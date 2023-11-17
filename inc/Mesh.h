#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "Shader.h"

// Note: should use GLfloat?
struct Vertex {
    float x, y, z;
};

class Mesh {
 public:
     ~Mesh();
     Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

     void draw(Shader& shader, double currentTime) const;

 private:
     GLuint vao;   // Vertex array object
     GLuint vbo;    // Vertex buffer object
     GLuint ebo;    // Element array buffer

     Vec3f position;
     std::vector<Vertex> vertices;
     std::vector<unsigned int> indices;

     void setupMesh();
};

#endif
