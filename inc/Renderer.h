#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

#include "Shader.h"
#include "math.h"

class Renderer {
 public:
    Renderer();
    ~Renderer();
    void render(Shader& shader);

 private:
    // Vertex buffer object
    GLuint vbo;
    // Vertex array object
    GLuint vao;
};

#endif  // INC_RENDERER_H_
