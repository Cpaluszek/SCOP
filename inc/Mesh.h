#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "Shader.h"

struct Vertex {
    GLfloat x, y, z;
    GLfloat r, g, b;
};

class Mesh {
 public:
     ~Mesh();
     Mesh(const std::vector<Vertex>& vertices);

     void draw(Shader& shader, double currentTime) const;

 private:
     GLuint vao;   // Vertex array object
     GLuint vbo;    // Vertex buffer object
     // GLuint ebo;    // Element array buffer

     Vec3f position;
     std::vector<Vertex> vertices;

     void setupMesh();
     void computVerticesColors();
};

#endif
