#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <cmath>
#include <vector>

#include "glew.h"
#include "math.h"
#include "Shader.h"
#include "Vertex.h"

class Mesh {
 public:
     explicit Mesh(VertexVector& vertices);
     ~Mesh();

     void draw(Shader& shader, float deltaTime);
     void resetTransform();
     Vec3f position;
     Vec3f rotation;

 private:
     GLuint vao = 0;   // Vertex array object
     GLuint vbo = 0;    // Vertex buffer object

     Vec3f origin;
     VertexVector vertices;

     void setupMesh();
     void mapTextureCoordinates();
     void findObjectOrigin();
};

#endif
