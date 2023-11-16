#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <vector>
#include "../lib/GLEW/include/glew.h"
#include "Camera.h"
#include "Shader.h"

// Note: store Vertex & color in same array?
// Note: should use GLfloat?
struct Vertex {
    float x, y, z;
};

struct VertexColor {
    float r, g, b;
};

class Mesh {
 public:
     ~Mesh();
     Mesh();
     Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

     // Todo: make private?
     Vec3f position;
     std::vector<Vertex> vertices;
     std::vector<VertexColor> verticesColors;
     std::vector<unsigned int> indices;

     void setupMesh();
     void draw(Shader& shader, double currentTime) const;

 private:
     // void computeVertexColor();

     // Vertex array object
     GLuint vao;
     // Vertex buffer object
     GLuint vbo;
     // Element array buffer
     GLuint ebo;
};

#endif
