#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

#include "./Camera.h"
#include "./Mesh.h"
#include "./Shader.h"
#include "./Window.h"
#include "./math.h"

class Renderer {
 public:
     explicit Renderer(Camera const& camera);
     ~Renderer();

     void render(Mesh const& mesh);

     void BindMeshData(Mesh const& mesh);

 private:
    // Vertex buffer object
    GLuint vbo;
    // Vertex array object
    GLuint vao;

    Shader* shader;

    Camera const& camera;
};

#endif  // INC_RENDERER_H_
