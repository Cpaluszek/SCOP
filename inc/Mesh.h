#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "Shader.h"

// Note: store Vertex & color in same array?
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
     // Vertex array object
     GLuint vao;
     // Vertex buffer object
     GLuint vbo;
     // Element array buffer
     GLuint ebo;

     Vec3f position;
     std::vector<Vertex> vertices;
     std::vector<unsigned int> indices;

     void setupMesh();
};

#endif
