#include <complex>
#include <iostream>
#include <ostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"
#include "../inc/Camera.h"

#include "../inc/math.h"

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq

// Todo: LSPzero Format on save

// Todo: use cmake
// Todo: remove glm lib

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
	Mat4f projection = Mat4f::perspective(math::radians(camera.Zoom), 
				800.0f / 600.0f, 0.1f, 100.0f);
    projection = Mat4f::transpose(projection);
	customShader.setMat4("projection", projection);

	Mat4f view = camera.GetViewMatrix();
    view = Mat4f::transpose(view);
	customShader.setMat4("view", view);

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        renderer.Render(customShader);

        window.updateDisplay();
    }
    return 0;
}

