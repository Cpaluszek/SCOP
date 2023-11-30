#ifndef INC_VERTEX_H_
#define INC_VERTEX_H_

#include <vector>
#include "glew.h"
#include "math.h"

struct Vertex {
    Vec3f position;
    Vec3f normal;
    Vec3f color;
    GLfloat textX = 0.0f;
    GLfloat textY = 0.0f;
};

enum Vertex_Format {
    VERTEX,
    VERTEX_TEXTURE,
    VERTEX_TEXTURE_NORMAL,
    VERTEX_NORMAL
};


typedef std::vector<Vertex> VertexVector;

#endif  //INC_VERTEX_H_
