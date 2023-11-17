#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "./Camera.h"
#include "./Window.h"

#include "../lib/GLFW/include/glfw3.h"

class Input {
 public:
     Input(Camera& camera, GLFWwindow* windowInstance);
     void processInput(const float deltaTime);

 private:
     Camera& camera;
     GLFWwindow* window;

     bool polygonMode;
};

#endif  // INC_INPUT_H_
