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

int main() {

	glm::mat4 id = glm::mat4(1.0f);
	glm::mat4 id2 = glm::mat4(2.0f);
	std::cout << glm::to_string(id) << std::endl;

	Mat4f identity(1.0f);
	std::cout << "identity:" << std::endl;
	std::cout << identity << std::endl;

	Mat4f test(2.0f);
	std::cout << "Add:" << std::endl;
	std::cout << identity + test << std::endl;

	std::cout << "Substract:" << std::endl;
	std::cout << identity - test << std::endl;

	std::cout << "Mult:" << std::endl;
	std::cout << identity * test << std::endl;
	std::cout << glm::to_string(id * id2) << std::endl;

	std::cout << "Translate:" << std::endl;
	std::cout << Mat4f::translate(identity, Vec3f(1.0f, 2.0f, 3.0f)) << std::endl;
	std::cout << glm::to_string(glm::translate(id, glm::vec3(1.0f, 2.0f, 3.0f))) << std::endl;

	std::cout << "Rotate:" << std::endl;
	std::cout << Mat4f::rotate(identity, 1.5708f, Vec3f(1.0f, 0.0f, 0.0f)) << std::endl;

	glm::mat4 model = glm::mat4(1.0f);
	std::cout << glm::to_string(glm::rotate(model, 1.5708f, glm::vec3(1.0f, 0.0f, 0.0f))) << std::endl;
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

