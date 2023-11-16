#include <exception>

#include "../inc/Input.h"
#include "../inc/Model.h"
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

int main(const int argc, char *argv[]) {

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
        std::cerr << "Failed to create GLFW window" << std::endl;
        return EXIT_FAILURE;
    }

    if (!window.initGlew()) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    Camera camera;

    // Note: pass by reference or pointer
    Renderer renderer(camera);
    const Input input(camera, window.instance);

    Model* model = nullptr;
    try {
        model = new Model(program_options::inputFile());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    if (model == nullptr) {
        // Todo: test
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window.instance)) {
        input.processInput(getDeltaTime());

        renderer.render(model);

        window.updateDisplay();
    }
    return EXIT_SUCCESS;
}

// Note: move to utils?
float getDeltaTime() {
    static float lastFrameTime = 0.0f;
    const auto currentTime = static_cast<float>(glfwGetTime());
    const float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    return deltaTime;
}

