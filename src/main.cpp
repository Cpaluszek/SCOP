#include <iostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"

void processInput(GLFWwindow *window);

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq
// Todo: LSPzero Format on save

int main() {
    Window window;

    if (window.instance == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

	if (!window.InitGlew()) {
		return -1;
	}

    Renderer renderer;

    Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    customShader.use();

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        renderer.Render();

        glfwSwapBuffers(window.instance);
        glfwPollEvents();
    }

    return 0;
}

