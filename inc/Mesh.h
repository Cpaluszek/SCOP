#ifndef INC_MESH_H_
#define INC_MESH_H_

#include <cmath>
#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "./math.h"
#include "./Shader.h"

struct Vertex {
    Vec3f position;
    Vec3f normal;       // Todo: use normals in shaders
    Vec3f color;
    GLfloat textX, textY;
};

typedef std::vector<Vertex> VertexVector;

class Mesh {
 public:
     ~Mesh();
     Mesh(const std::vector<Vertex>& vertices);

     void draw(Shader& shader, double currentTime) const;
     Vec3f position;

 private:
     GLuint vao;   // Vertex array object
     GLuint vbo;    // Vertex buffer object

     Vec3f origin;
     std::vector<Vertex> vertices;

     void setupMesh();
     void mapTextureCoordinates();
     void findObjectOrigin();
};

#endif
