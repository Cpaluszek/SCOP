#include <exception>

#include "Input.h"
#include "Model.h"
#include "Renderer.h"
#include "Window.h"

#include "program_options.h"

int main(const int argc, char *argv[]) {
    try {
        program_options::parse(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./SCOP <obj file>" << std::endl;
        return EXIT_FAILURE;
    }

    Camera camera(CAM_START_POSITION);
    Input input;
    Model model;
    Renderer renderer;
    Window window;

    try {
        window.init();
        input.setWindow(window.instance);
        renderer.loadShader();
        model.loadObjFile(program_options::inputFile());
        model.loadTexture("./resources/textures/uvmap.jpeg");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    input.printKeyBinds();

    while (!glfwWindowShouldClose(window.instance)) {
        float deltaTime = Window::getDeltaTime();

        input.processInput(model, camera, deltaTime);

        renderer.render(camera, model, deltaTime);

        window.updateDisplay();
    }
    return EXIT_SUCCESS;
}

