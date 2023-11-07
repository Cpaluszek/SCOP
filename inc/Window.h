#ifndef SCOP_WINDOW_H
#define SCOP_WINDOW_H

#include <string>
#include <iostream>
#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"
#include "../lib/GLFW/include/glfw3.h"

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

class Window {
 public:
    // Note: static instance? static getter?
    // Note: any interest in singleton pattern?
    GLFWwindow *instance;

    Window();
    ~Window();

    bool InitGlew();
    void processInput();
    void updateDisplay();
};


#endif //SCOP_WINDOW_H
