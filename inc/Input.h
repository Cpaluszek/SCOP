#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "./Camera.h"
#include "./Model.h"
#include "./Window.h"

#include "../lib/GLFW/include/glfw3.h"
#include <unordered_map>

class Input {
 public:
     Input(Camera& camera, GLFWwindow* windowInstance);
     void processInput(Model& model, const float deltaTime);

 private:
     Camera& camera;
     GLFWwindow* window;


     std::unordered_map<int, bool> keyStateMap;

     void resetKeyState();
};

#endif  // INC_INPUT_H_
