#include <cstdlib>
#include <exception>
#include <fstream>
#include <ostream>
#include <string>

#include "../inc/Input.h"
#include "../inc/Mesh.h"
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

int main(int argc, char *argv[]) {

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

    //////////////////////////////////////////
    std::string inputFile = program_options::inputFile();
    std::ifstream objFile(inputFile, std::ios::in);
    // if (!objFile.is_open()) {
    //     throw std::runtime_error("Could not open input file '" + inputFile + "'!");
    // }
    std::string line;
    std::vector<Vertex> parsedVertices;
    std::vector<unsigned int> parsedIndices;

    while (std::getline(objFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        } else if (line[0] == 'v') {
            std::istringstream iss(line);

            char v;
            iss >> v;

            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            parsedVertices.push_back(vertex);
        } else if (line[0] == 'f') {
            char f;

            std::istringstream iss(line);
            iss >> f;

            int num;
            int count = 0;
            while (iss >> num) {
                // Todo: if num is negative
                if (count++ == 3) {
                    int a = *(parsedIndices.rbegin() + 3 - 1);
                    int b = *(parsedIndices.rbegin() + 1 - 1);
                    parsedIndices.push_back(a);
                    parsedIndices.push_back(b);
                }
                parsedIndices.push_back(num - 1); 
            }
            
        }
    }
    objFile.close();
    Mesh meshTest = Mesh(parsedVertices, parsedIndices);


    Model model(program_options::inputFile());

    std::cout << "test: " << model.mesh.vertices.size() << std::endl;

    while (!glfwWindowShouldClose(window.instance)) {
        input.processInput(getDeltaTime());

        renderer.render(model, meshTest);

        window.updateDisplay();
        break ;
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

