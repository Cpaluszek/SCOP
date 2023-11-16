#include "../inc/Input.h"
#include "glfw3.h"

Input::Input(Camera& camera, GLFWwindow* windowInstance)
: camera(camera), window(windowInstance) {}

void Input::processInput(const float deltaTime) const {
    if (this->window == nullptr) {
        // Note: use exception?
        return;
    }
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    // Camera Translation
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboardInput(FORWARD, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboardInput(BACKWARD, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboardInput(LEFT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboardInput(RIGHT, deltaTime);
    }

    // Camera Rotation
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_RIGHT, deltaTime);
    }

    // Reset Camera
    if (glfwGetKey(this->window, GLFW_KEY_SPACE)) {
        camera.reset();
    }
}

