#ifndef INC_WINDOW_H_
#define INC_WINDOW_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"
#include "./settings.h"

class Window {
 public:
    GLFWwindow* instance;

    ~Window();

    void init();

    void updateDisplay() const;

    static float getDeltaTime();

 private:
    static void checkGlfwError();
};

#endif  // INC_WINDOW_H_
