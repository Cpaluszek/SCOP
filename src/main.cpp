#include <iostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"

#include "../inc/math/Vec3f.h"

void processInput(GLFWwindow *window);

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq
// Todo: LSPzero Format on save

int main() {
    Window window;

	Vec3f a(1.0f, 2.0f, 3.0f);
	Vec3f b(4.0f, 5.0f, 6.0f);
	Vec3f right(1.0f, 0.0f, 0.0f);
	Vec3f front(0.0f, 1.0f, 0.0f);

	Vec3f sum = a + b;
	Vec3f diff = a - b;
	float dot = Vec3f::dot(a, b);
	Vec3f cross = Vec3f::cross(right, front);
	double len = a.length();
	double sqrlen = a.sqrLength();

	std::cout << "sum: " << sum << std::endl;
	std::cout << "diff: " << diff << std::endl;
	std::cout << "dot: " << dot << std::endl;
	std::cout << "cross: " << cross << std::endl;
	std::cout << "len: " << len << std::endl;
	std::cout << "sqrlen: " << sqrlen << std::endl;

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

