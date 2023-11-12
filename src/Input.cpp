#include "../inc/Input.h"

void Input::processInput() const {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }
}

void Input::setCamera(Camera* camera) {
    this->camera = camera;
}

void Input::setWindow(GLFWwindow* window) {
    this->window = window;
}

