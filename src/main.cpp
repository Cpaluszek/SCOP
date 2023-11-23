#include <exception>
#include <memory>

#include "../inc/Input.h"
#include "../inc/Model.h"
#include "../inc/Renderer.h"
#include "../inc/Window.h"

#include "../inc/program_options.h"
#include "../inc/math.h"
#include "glfw3.h"

// Todo: use cmake

// Todo: check https://learnopengl.com/Advanced-OpenGL/Face-culling
int main(const int argc, char *argv[]) {
    try {
        program_options::parse(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./SCOP <obj file>" << std::endl;
        return EXIT_FAILURE;
    }

    Camera camera;
    Renderer renderer(camera);
    std::unique_ptr<Window> window(new Window);
    std::unique_ptr<Model> model(new Model);
    try {
        window->init();
        renderer.loadShader();
        model->loadObjFile(program_options::inputFile());
        model->loadTexture("./resources/textures/uvmap.jpeg");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    Input input(camera, window->instance);

    while (!glfwWindowShouldClose(window->instance)) {
        float deltaTime = Window::getDeltaTime();

        input.processInput(*model, deltaTime);

        renderer.render(*model, deltaTime);

        window->updateDisplay();
    }
    return EXIT_SUCCESS;
}

