#include "../inc/Input.h"
#include "glfw3.h"

Input::Input(Camera& camera, GLFWwindow* windowInstance)
: camera(camera), window(windowInstance) {
    std::cout << "----- Keybinds: -----" << std::endl;
    std::cout << " Object movements:" << std::endl;
    std::cout << "  W: move up" << std::endl;
    std::cout << "  A: move left" << std::endl;
    std::cout << "  S: move down" << std::endl;
    std::cout << "  D: move right" << std::endl;
    std::cout << "  R: move forward" << std::endl;
    std::cout << "  F: move backward" << std::endl;
    std::cout << " Object Rotation:" << std::endl;
    std::cout << "  TODO" << std::endl;
    std::cout << " Polygon Mode:" << std::endl;
    std::cout << "  P: switch between wireframe and fill" << std::endl;
    std::cout << "---------------------" << std::endl;

}

void Input::processInput(Model& model, const float deltaTime) { 
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

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
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
        model.processKeyboardInput(UP, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
        model.processKeyboardInput(DOWN, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
        model.processKeyboardInput(LEFT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
        model.processKeyboardInput(RIGHT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS) {
        model.processKeyboardInput(BACKWARD, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS) {
        model.processKeyboardInput(FORWARD, deltaTime);
    }

    // Todo: Reset Model
    // if (!this->keyStateMap[GLFW_KEY_SPACE] && glfwGetKey(this->window, GLFW_KEY_SPACE)) {
    //     this->keyStateMap[GLFW_KEY_SPACE] = true;
    //     camera.reset();
    // }

    this->resetKeyState();
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
