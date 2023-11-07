#ifndef SCOP_RENDERER_H
#define SCOP_RENDERER_H

#include "../lib/GLEW/include/glew.h"

class Renderer {
 public:
    Renderer();
    ~Renderer();
    void Render();

private:
    // Vertex buffer object
    GLuint VBO;
    // Vertex array object
    GLuint VAO;
};

#endif //SCOP_RENDERER_H
