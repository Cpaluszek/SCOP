#include "Input.h"
#include "glfw3.h"

void Input::printKeyBinds() const {
    std::cout << ANSI_COLOR_YELLOW << "------------- Key binds: -------------" << ANSI_RESET << std::endl;
    std::cout << "   Esc: Close window" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Object Movements:" << ANSI_RESET << std::endl;
    std::cout << "   W: Move Up" << std::endl;
    std::cout << "   A: Move Left" << std::endl;
    std::cout << "   S: Move Down" << std::endl;
    std::cout << "   D: Move Right" << std::endl;
    std::cout << "   R: Move Backward" << std::endl;
    std::cout << "   F: Move Forward" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Object Rotation:" << ANSI_RESET << std::endl;
    std::cout << "   H    : Toggle auto rotation" << std::endl;
    std::cout << "   I - K: x axis rotation" << std::endl;
    std::cout << "   J - L: y axis rotation" << std::endl;
    std::cout << "   U - O: z axis rotation" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Polygon Mode:" << ANSI_RESET << std::endl;
    std::cout << "   P: Switch between Wireframe and Fill" << std::endl;
    std::cout << ANSI_COLOR_CYAN << " Texture:" << ANSI_RESET << std::endl;
    std::cout << "   T: Change texture" << std::endl;
    std::cout << "   C: Switch between Texture and Color" << std::endl;
    std::cout << ANSI_COLOR_YELLOW << "--------------------------------------" << ANSI_RESET << std::endl;
}

void Input::setWindow(GLFWwindow* instance) {
    if (instance == nullptr) {
        throw std::runtime_error("Window instance is null");
    }
    this->window = instance;
}

void Input::processInput(Model& model, Camera& camera, const float deltaTime) { 
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    // Camera zoom
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.processKeyboardInput(ZOOM_IN, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.processKeyboardInput(ZOOM_OUT, deltaTime);
    }

    // Toggle wireframe
    if (!this->keyStateMap[GLFW_KEY_P] && glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_P] = true;
        model.switchPolygonMode();
    }
    // texture
    if (!this->keyStateMap[GLFW_KEY_C] && glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_C] = true;
        model.switchTextureMode();
    }
    if (!this->keyStateMap[GLFW_KEY_T] && glfwGetKey(this->window, GLFW_KEY_T) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_T] = true;
        model.switchTexture();
    }
    // Movement
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
        model.resetTransform();
    }
    if (glfwGetKey(this->window, GLFW_KEY_I) == GLFW_PRESS) {
        model.processKeyboardInput(X_ROT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_K) == GLFW_PRESS) {
        model.processKeyboardInput(X_ROT_INV, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_J) == GLFW_PRESS) {
        model.processKeyboardInput(Y_ROT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_L) == GLFW_PRESS) {
        model.processKeyboardInput(Y_ROT_INV, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS) {
        model.processKeyboardInput(Z_ROT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_O) == GLFW_PRESS) {
        model.processKeyboardInput(Z_ROT_INV, deltaTime);
    }

    // Rotations
    if (!this->keyStateMap[GLFW_KEY_H] && glfwGetKey(this->window, GLFW_KEY_H) == GLFW_PRESS) {
        this->keyStateMap[GLFW_KEY_H] = true;
        model.toggleAutoRotation();
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
