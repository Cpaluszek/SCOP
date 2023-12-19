#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <cmath>
#include <vector>

#include "glew.h"
#include "math.h"
#include "settings.h"
#include "Shader.h"
#include "Vertex.h"

class Mesh {
 public:
     explicit Mesh(VertexVector& vertices, Vertex_Format& format);
     ~Mesh();

     void draw(Shader& shader) const;
     void resetTransform();

     void sphericalUVMapping();
     void cubicUVMapping();
     void updateTextureAttrib();

     Vec3f position;
     Vec3f rotation;

 private:
     GLuint vao = 0;   // Vertex array object
     GLuint vbo = 0;    // Vertex buffer object

     Vec3f initialPosition;
     Vec3f origin;
     VertexVector vertices;
     Vertex_Format format;

     void setupMesh();
     void computeObjectPosition();
};

#endif
