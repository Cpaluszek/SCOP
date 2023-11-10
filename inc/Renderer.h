#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "../lib/GLEW/include/glew.h"
#include "../lib/glm/glm.hpp"

#include "Shader.h"
#include "math/Vec3f.h"
#include "math/Mat4f.h"

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
