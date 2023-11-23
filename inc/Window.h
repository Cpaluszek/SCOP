#ifndef INC_WINDOW_H_
#define INC_WINDOW_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

constexpr unsigned int WIN_WIDTH = 1200;
constexpr unsigned int WIN_HEIGHT = 900;

// Todo: store all settings in a single header file
constexpr float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);

class Window {
 public:
    GLFWwindow* instance;

    ~Window();

    void init();

    void updateDisplay() const;

    static float getDeltaTime();

 private:
    const char* glfwErrorDescription;
    int glfwErrorCode;

    void checkGlfwError();
};

#endif  // INC_WINDOW_H_
