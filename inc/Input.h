#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "./Model.h"
#include "./settings.h"
#include "./Window.h"

#include "../lib/GLFW/include/glfw3.h"
#include <unordered_map>

class Input {
 public:
     explicit Input(GLFWwindow* windowInstance);
     void processInput(Model& model, float deltaTime);

 private:
     GLFWwindow* window;


     std::unordered_map<int, bool> keyStateMap;

     void resetKeyState();
};

#endif  // INC_INPUT_H_
