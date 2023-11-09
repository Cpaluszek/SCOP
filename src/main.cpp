#include <iostream>
#include <ostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"

#include "../inc/math/Mat4f.h"

void processInput(GLFWwindow *window);

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq
// Todo: LSPzero Format on save

int main() {
	Mat4f zero;
	std::cout << "zero:" << std::endl;
	std::cout << zero << std::endl;

	Mat4f identity(1.0f);
	std::cout << "identity:" << std::endl;
	std::cout << identity << std::endl;

	Mat4f test(2.0f);
	std::cout << "Add:" << std::endl;
	std::cout << zero + test << std::endl;

	std::cout << "Substract:" << std::endl;
	std::cout << zero - test << std::endl;

	std::cout << "Mult:" << std::endl;
	std::cout << identity * test << std::endl;

	std::cout << "Translate:" << std::endl;
	std::cout << Mat4f::translate(identity, Vec3f(1.0f, 2.0f, 3.0f)) << std::endl;
    // Window window;
    //
    // if (window.instance == nullptr) {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     return -1;
    // }
    //
    // if (!window.InitGlew())
    //     return -1;
    //
    // Renderer renderer;
    //
    // Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    // customShader.use();
    //
    // while (!glfwWindowShouldClose(window.instance)) {
    //     window.processInput();
    //
    //     renderer.Render();
    //
    //     window.updateDisplay();
    // }
    // return 0;
}

