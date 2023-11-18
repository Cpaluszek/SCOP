#include "../inc/Input.h"
#include "glfw3.h"

Input::Input(Camera& camera, GLFWwindow* windowInstance)
: camera(camera), window(windowInstance) {}

void Input::processInput(Model& model, const float deltaTime) { 
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    this->cameraInput(deltaTime);

    // Toggle wireframe
    if (!this->keyStateMap[GLFW_KEY_P] && glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_P] = true;
        model.polygonMode ^= true;
    }

    // use texture
    if (!this->keyStateMap[GLFW_KEY_T] && glfwGetKey(this->window, GLFW_KEY_T) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_T] = true;
        model.useTexture ^= true;
    }

    this->resetKeyState();
}

void Input::cameraInput(const float deltaTime) {

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
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.processKeyboardInput(UP, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.processKeyboardInput(DOWN, deltaTime);
    }

    // Camera Rotation
    // Note: use numpad instead?
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        camera.processKeyboardInput(ROTATE_DOWN, deltaTime);
    }
    
    // Reset Camera
    if (!this->keyStateMap[GLFW_KEY_SPACE] && glfwGetKey(this->window, GLFW_KEY_SPACE)) {
        this->keyStateMap[GLFW_KEY_SPACE] = true;
        camera.reset();
    }
}

void Input::resetKeyState() {
    for (auto &keyState: this->keyStateMap) {
        int key = keyState.first;
        bool &state = keyState.second;

        if (state && glfwGetKey(this->window, key) == GLFW_RELEASE) {
            state = false;
        }
    }
}
