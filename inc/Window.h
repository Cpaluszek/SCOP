#ifndef INC_WINDOW_H_
#define INC_WINDOW_H_

#include <string>
#include <iostream>
#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

class Window {
 public:
    // Note: static instance? static getter?
    // Note: any interest in singleton pattern?
    GLFWwindow* instance;

    Window();
    ~Window();

    bool initGlew();
    void processInput();
    void updateDisplay();
};

#endif  // INC_WINDOW_H_
