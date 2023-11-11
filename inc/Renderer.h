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
    void Render(Shader& shader);

 private:
    // Vertex buffer object
    GLuint VBO;
    // Vertex array object
    GLuint VAO;
};

#endif  // INC_RENDERER_H_
