#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

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

    /////////////////////////////////////////
    // Parse arguments
    try {
        program_options::parse(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./SCOP <obj file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Todo: move to another file
    std::ifstream objFile(program_options::inputFile(), std::ios::in);
    if (!objFile.is_open()) {
        std::cerr << "Could not open input file '" << program_options::inputFile() << "'!" << std::endl;
        return EXIT_FAILURE;
    }
    // [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
    // o [object name]
    // ...
    //  g [group name]
    //  ...
    //
    // mtllib [external .mtl file format] -> Reference materials
    // usmtl [material name] -> material name specified in .mtl file
    //
    // s off -> smooth shading
    //
    // v x y z [w] -> vertex position (w) is optionnal - default to 1.0
    //
    // f v1 v2 v3 ... -> faces elements (start at 1) - -1 refers to the last

    // Todo: order matter
    // v -> f


    // Note: [LearnOpenGL - Mesh](https://learnopengl.com/Model-Loading/Mesh)

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
            std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
            parsedVertices.push_back(vertex);
        } else if (line[0] == 'f') {
            char f;

            std::istringstream iss(line);
            iss >> f;

            int num;
            while (iss >> num) {
                // Todo: if num is negative
                parsedIndices.push_back(num - 1); 
                // Note: if 4 values -> convert to 2 triangles?
            }
            
        }
    }

    objFile.close();
    /////////////////////////////////////////
    
    // Todo: need to use DrawElements;

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

    Mesh mesh(Vec3f(0.0f, 0.0f, -5.0f));
    mesh.setVertices(parsedVertices);
    mesh.setIndices(parsedIndices);
    renderer.BindMeshData(mesh);

    while (!glfwWindowShouldClose(window.instance)) {
        input.processInput(getDeltaTime());

        renderer.render(mesh);

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

