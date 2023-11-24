#include "Window.h"

void Window::init() {
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

    this->instance = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "SCOP", nullptr, nullptr);
    this->checkGlfwError();

    glfwMakeContextCurrent(this->instance);
    this->checkGlfwError();

    // Init GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::stringstream errorMessage;
        errorMessage << "GLEW error: " << glewGetErrorString(err);
        throw std::runtime_error(errorMessage.str());
    }
}

Window::~Window() {
    glfwDestroyWindow(this->instance);
    glfwTerminate();
}

void Window::updateDisplay() const {
    glfwSwapBuffers(this->instance);
    glfwPollEvents();
}

float Window::getDeltaTime() {
    static float lastFrameTime = 0.0f;
    const auto currentTime = static_cast<float>(glfwGetTime());
    const float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    return deltaTime;
}

void Window::checkGlfwError() {
    const char* glfwErrorDescription;
    int glfwErrorCode = glfwGetError(&glfwErrorDescription);
    if (glfwErrorCode != GLFW_NO_ERROR) {
        std::stringstream errorMessage;
        errorMessage << "GLFW error: " << glfwErrorCode << " - " << glfwErrorDescription;
        throw std::runtime_error(errorMessage.str());
    }
}

