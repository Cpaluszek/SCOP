#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include <stdexcept>
#include <unordered_map>

#include "Model.h"
#include "settings.h"
#include "Window.h"

#include "glfw3.h"

class Input {
 public:
     Input();

     void setWindow(GLFWwindow* instance);
     void processInput(Model& model, float deltaTime);

 private:
     GLFWwindow* window;

     std::unordered_map<int, bool> keyStateMap;

     void resetKeyState();
};

#endif  // INC_INPUT_H_
