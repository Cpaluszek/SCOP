#include "../inc/Window.h"
#include "glfw3.h"
#include <stdexcept>

Window::Window() {
    if (!glfwInit()) {
        this->instance = nullptr;
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Configure GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Todo: remove
    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    this->instance = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "SCOP", nullptr, nullptr);

    if (this->instance == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(this->instance);

    // Init GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "glewInit err: " << glewGetErrorString(err) << std::endl;
    }
}

Window::~Window() {
    glfwTerminate();
}

void Window::updateDisplay() const {
    glfwSwapBuffers(this->instance);
    glfwPollEvents();
}

