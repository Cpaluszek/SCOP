#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>

#include "../inc/Input.h"
#include "../inc/Mesh.h"
#include "../inc/Renderer.h"
#include "../inc/Window.h"

#include "../inc/program_options.h"
#include "../inc/math.h"
#include "glfw3.h"

// Todo: stb_image.h authorized?
// Todo: check for smart_ptr usage - shared - uniqueq

// Todo: LSPzero Format on save

// Todo: use cmake

float getDeltaTime();

int main(int argc, char *argv[]) {

    // Parse arguments
    try {
        program_options::parse(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./SCOP <obj file>" << std::endl;
        return EXIT_FAILURE;
    }




    Window window;
    if (window.instance == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return EXIT_FAILURE;
    }

    if (!window.initGlew()) {
        return EXIT_FAILURE;
    }

    Camera camera;

    // Note: pass by reference or pointer
    Renderer renderer(camera);
    Input input;
    input.setCamera(&camera);
    input.setWindow(window.instance);

    Mesh cube(Vec3f(0.0f, 0.0f, -5.0f));
    renderer.BindMeshData(cube);

    while (!glfwWindowShouldClose(window.instance)) {
        input.processInput(getDeltaTime());

        renderer.render(cube);

        window.updateDisplay();
    }
    return EXIT_SUCCESS;
}

float getDeltaTime() {
    static float lastFrameTime = 0.0f;
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    return deltaTime;
}

