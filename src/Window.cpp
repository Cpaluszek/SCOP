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

    if (this->instance == nullptr) {
        return;
    }
    glfwMakeContextCurrent(this->instance);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::initGlew() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "glewInit err: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    return true;
}

void Window::updateDisplay() {
    glfwSwapBuffers(this->instance);
    glfwPollEvents();
}

