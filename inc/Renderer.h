#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

#include "./Camera.h"
#include "./Model.h"
#include "./Shader.h"
#include "./math.h"

class Renderer {
 public:
     void loadShader();

     void render(const Camera& camera, Model& model, float deltaTime);

 private:
    Shader shader;
};

#endif  // INC_RENDERER_H_
