#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <cmath>
#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "./math.h"
#include "./Shader.h"
#include "./Vertex.h"

class Mesh {
 public:
     ~Mesh();
     Mesh(const VertexVector& vertices);

     void draw(Shader& shader, double currentTime) const;
     Vec3f position;

 private:
     GLuint vao;   // Vertex array object
     GLuint vbo;    // Vertex buffer object

     Vec3f origin;
     VertexVector vertices;

     void setupMesh();
     void mapTextureCoordinates();
     void findObjectOrigin();
};

#endif
