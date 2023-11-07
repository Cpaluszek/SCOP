#ifndef SCOP_GLFWWINDOW_H
#define SCOP_GLFWWINDOW_H

#include "../lib/GLFW/include/glfw3.h"

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

class GlfwWindow {
 public:
    GLFWwindow *instance;

    GlfwWindow();
    ~GlfwWindow();

};


#endif //SCOP_GLFWWINDOW_H
