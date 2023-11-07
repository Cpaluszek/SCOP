#include "../inc/Window.h"

Window::Window() {
    if (!glfwInit()) {
        this->instance = nullptr;
		return;
    }

    // Configure GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    this->instance = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "SCOP", nullptr, nullptr);

    if (this->instance != nullptr) {
        glfwMakeContextCurrent(this->instance);     // Make the window's context current
    }
}

Window::~Window() {
    glfwTerminate();
}
