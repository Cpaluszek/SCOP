#ifndef SCOP_WINDOW_H
#define SCOP_WINDOW_H

#include "../lib/GLFW/include/glfw3.h"

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

class Window {
 public:
    GLFWwindow *instance;

    Window();
    ~Window();
};


#endif //SCOP_WINDOW_H
