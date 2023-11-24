#include "../inc/Input.h"
#include "glfw3.h"

Input::Input() {
    std::cout << ANSI_COLOR_YELLOW << "------------- Key binds: -------------" << ANSI_RESET << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Object Movements:" << ANSI_RESET << std::endl;
    std::cout << "   W: Move Up" << std::endl;
    std::cout << "   A: Move Left" << std::endl;
    std::cout << "   S: Move Down" << std::endl;
    std::cout << "   D: Move Right" << std::endl;
    std::cout << "   R: Move Forward" << std::endl;
    std::cout << "   F: Move Backward" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Object Rotation:" << ANSI_RESET << std::endl;
    std::cout << "   TODO" << std::endl; // Placeholder for rotation controls
    std::cout << ANSI_COLOR_CYAN << " Polygon Mode:" << ANSI_RESET << std::endl;
    std::cout << "   P: Switch between Wireframe and Fill" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Texture:" << ANSI_RESET << std::endl;
    std::cout << "   T: Switch between Texture and Color" << std::endl;
    std::cout << ANSI_COLOR_YELLOW << "--------------------------------------" << ANSI_RESET << std::endl;
}

void Input::setWindow(GLFWwindow* instance) {
    if (instance == nullptr) {
        throw std::runtime_error("Window instance is null");
    }
    this->window = instance;
}

void Input::processInput(Model& model, const float deltaTime) { 
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    // Toggle wireframe
    if (!this->keyStateMap[GLFW_KEY_P] && glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_P] = true;
        model.switchPolygonMode();
    }

    // use texture
    if (!this->keyStateMap[GLFW_KEY_T] && glfwGetKey(this->window, GLFW_KEY_T) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_T] = true;
        model.switchTextureMode();
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

    if (!this->keyStateMap[GLFW_KEY_SPACE] && glfwGetKey(this->window, GLFW_KEY_SPACE)) {
        this->keyStateMap[GLFW_KEY_SPACE] = true;
        model.resetPosition();
    }

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
