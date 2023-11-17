#include <exception>

#include "../inc/Input.h"
#include "../inc/Model.h"
#include "../inc/Renderer.h"
#include "../inc/Window.h"

#include "../inc/program_options.h"
#include "../inc/math.h"
#include "glfw3.h"

// Todo: stb_image.h authorized?

// Todo: use cmake

// Todo: check https://learnopengl.com/Advanced-OpenGL/Face-culling
int main(const int argc, char *argv[]) {
    // Check for program arguments
    try {
        program_options::parse(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./SCOP <obj file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Create glfw window
    Window* window;
    try {
        window = new Window();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Init program systems
    Camera camera;
    Renderer renderer(camera);
    Input input(camera, window->instance);

    Model* model;
    try {
        model = new Model(program_options::inputFile());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        delete window;
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window->instance)) {
        input.processInput(Window::getDeltaTime());

        renderer.render(model);

        window->updateDisplay();
    }
    delete model;
    delete window;
    return EXIT_SUCCESS;
}

