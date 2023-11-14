#ifndef INC_MESH_H_
#define INC_MESH_H_

#include "Camera.h"
#include <vector>

// Note: should use GLfloat?
struct Vertex {
    float x, y, z;
};

struct VertexColor {
    float r, g, b;
};

class Mesh {
 public:
     Mesh(Vec3f position);

     // Note: make private?
     Vec3f position;
     std::vector<Vertex> vertices;
     std::vector<VertexColor> verticesColors;

 private:
     void computeVertexColor();
};

#endif
