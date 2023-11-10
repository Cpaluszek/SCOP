#include <iostream>
#include <ostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"

#include "../inc/math/Mat4f.h"

// OpenGL Mathematics
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"
#include "../lib/glm/gtx/string_cast.hpp"

void processInput(GLFWwindow *window);

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq

// Todo: LSPzero Format on save

// Todo: use cmake

int main() {
    Window window;

    if (window.instance == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    if (!window.InitGlew())
        return -1;

    Renderer renderer;

    Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    customShader.use();

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        renderer.Render();

        window.updateDisplay();
    }
    return 0;
}

