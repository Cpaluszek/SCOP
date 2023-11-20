#ifndef INC_INPUT_H_
#define INC_INPUT_H_

// Define ANSI escape codes for text formatting
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_CYAN "\033[36m"
#define ANSI_COLOR_WHITE "\033[37m"

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
