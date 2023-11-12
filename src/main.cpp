#include <iostream>
#include <ostream>

#include "../inc/Input.h"
#include "../inc/Renderer.h"
#include "../inc/Window.h"

#include "../inc/math.h"
#include "glfw3.h"

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

    if (!window.initGlew()) {
        return -1;
    }

    Camera camera;

    // Note: pass by reference or pointer
    Renderer renderer(camera);
    Input input;
    input.setCamera(&camera);
    input.setWindow(window.instance);

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    while (!glfwWindowShouldClose(window.instance)) {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        input.processInput(deltaTime);

        renderer.render();

        window.updateDisplay();
    }
    return 0;
}

