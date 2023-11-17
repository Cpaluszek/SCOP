#ifndef INC_WINDOW_H_
#define INC_WINDOW_H_

#include <string>
#include <iostream>
#include "../lib/GLEW/include/glew.h"
#include "../lib/GLFW/include/glfw3.h"

constexpr unsigned int WIN_WIDTH = 1200;
constexpr unsigned int WIN_HEIGHT = 900;

// Todo: store all settings in a single header file
constexpr float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);

class Window {
 public:
    GLFWwindow* instance;

    Window();
    ~Window();

    void updateDisplay() const;

    static float getDeltaTime();
};

#endif  // INC_WINDOW_H_
