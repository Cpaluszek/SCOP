#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include <stdexcept>
#include <unordered_map>

#include "Camera.h"
#include "Model.h"
#include "settings.h"
#include "Window.h"

#include "glfw3.h"

class Input {
 public:
     void printKeyBinds() const;
     void setWindow(GLFWwindow* instance);
     void processInput(Model& model, Camera& camera, float deltaTime);

 private:
     GLFWwindow* window;

     std::unordered_map<int, bool> keyStateMap;

     void resetKeyState();
};

#endif  // INC_INPUT_H_
