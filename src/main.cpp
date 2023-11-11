#include <complex>
#include <iostream>
#include <ostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"
#include "../inc/Camera.h"

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

    if (!window.InitGlew()) {
        return -1;
	}

    Renderer renderer;

    Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    customShader.use();

	Vec3f cameraPos(0.0f, 0.0f, 3.0f);
	Camera camera;

	// Todo: clean
	// Mat4f projection = Mat4f::perspective(glm::radians(camera.Zoom), 
	// 			800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 projectionG = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	customShader.setMat4("projection", projectionG);
    std::cout << "Proj: " << glm::to_string(projectionG) << std::endl;

    glm::vec3 front;
    front.x = cos(glm::radians(-90.0f)) * cos(glm::radians(0.0f));
    front.y = sin(glm::radians(0.0f));
    front.z = sin(glm::radians(-90.0f)) * cos(glm::radians(0.0f));
    front = glm::normalize(front);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    up = glm::normalize(glm::cross(right, front));

	// Mat4f view = camera.GetViewMatrix();
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::mat4 view = glm::lookAt(camPos, camPos + front, up); 
    std::cout << "view: " << glm::to_string(view) << std::endl;

	customShader.setMat4("view", view);

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        renderer.Render(customShader);

        window.updateDisplay();
    }
    return 0;
}

