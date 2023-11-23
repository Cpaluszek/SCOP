#ifndef INC_VERTEX_H_
#define INC_VERTEX_H_

#include <vector>
#include "../lib/GLEW/include/glew.h"
#include "./math.h"

struct Vertex {
    Vec3f position;
    Vec3f normal;
    Vec3f color;
    GLfloat textX, textY;
};

typedef std::vector<Vertex> VertexVector;

#endif  //INC_VERTEX_H_