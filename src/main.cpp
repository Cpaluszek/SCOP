#include <complex>	// Note: complex?
#include <iostream>
#include <ostream>

#include "../inc/Window.h"
#include "../inc/Renderer.h"

#include "../inc/math.h"

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
    Renderer renderer(camera);

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        renderer.render();

        window.updateDisplay();
    }
    return 0;
}

