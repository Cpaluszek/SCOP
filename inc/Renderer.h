#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

#include "Camera.h"
#include "Shader.h"
#include "Window.h"
#include "math.h"

class Renderer {
 public:
    Renderer(Camera& camera);
    ~Renderer();
    void render();

 private:
    // Vertex buffer object
    GLuint vbo;
    // Vertex array object
    GLuint vao;

	Shader* shader;

	Camera& camera;
};

#endif  // INC_RENDERER_H_
