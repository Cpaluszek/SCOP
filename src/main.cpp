#include <exception>

#include "../inc/Input.h"
#include "../inc/Model.h"
#include "../inc/Renderer.h"
#include "../inc/Window.h"

#include "../inc/program_options.h"
#include "../inc/math.h"
#include "../inc/stb_image.h"
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

    // Todo: check for errors
    // Texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture parameters - wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nbChannels;
    unsigned char* data = stbi_load("./resources/textures/uvmap.jpeg", &width, &height, &nbChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);    
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    while (!glfwWindowShouldClose(window->instance)) {
        input.processInput(Window::getDeltaTime());

        renderer.render(model);

        window->updateDisplay();
    }
    delete model;
    delete window;
    return EXIT_SUCCESS;
}

