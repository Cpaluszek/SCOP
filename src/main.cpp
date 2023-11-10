#include <iostream>
#include <ostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"
#include "../inc/Renderer.h"

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
    glm::mat4 id = glm::mat4(1.0f);
    glm::mat4 id2 = glm::mat4(2.0f);
    // std::cout << glm::to_string(id) << std::endl;

    Mat4f mId(1.0f);
    Mat4f mId2(2.0f);
    std::cout << "---------------------" << std::endl;
    std::cout << "identity:" << std::endl;
    std::cout << mId << std::endl;
    std::cout << glm::to_string(id) << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "Mult:" << std::endl;
    std::cout << mId * mId2 << std::endl;
    std::cout << glm::to_string(id * id2) << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "Translate:" << std::endl;
    std::cout << Mat4f::translate(mId, Vec3f(1.0f, 2.0f, 3.0f)) << std::endl;
    std::cout << glm::to_string(glm::translate(id, glm::vec3(1.0f, 2.0f, 3.0f))) << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "Rotate:" << std::endl;
    std::cout << Mat4f::rotate(mId, 1.5708f, Vec3f(1.0f, 0.0f, 0.0f)) << std::endl;
    std::cout << glm::to_string(glm::rotate(id, 1.5708f, glm::vec3(1.0f, 0.0f, 0.0f))) << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "Scale:" << std::endl;
    std::cout << Mat4f::scale(mId, Vec3f(1.0f, 2.0f, 3.0f)) << std::endl;
    std::cout << glm::to_string(glm::scale(id, glm::vec3(1.0f, 2.0f, 3.0f)))<< std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "Perspective:" << std::endl;
    std::cout << glm::to_string(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)) << std::endl;
    std::cout << Mat4f::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f) << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "lookAt:" << std::endl;
    glm::vec3 cameraPos = glm::vec3(1.0f, 2.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    std::cout << glm::to_string(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)) << std::endl;
    Vec3f pos = Vec3f(1.0f, 2.0f, 3.0f);
    Vec3f front = Vec3f(0.0f, 0.0f, -1.0f);
    Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    std::cout << Mat4f::lookAt(pos, pos + front, up) << std::endl;
    // Window window;
    //
    // if (window.instance == nullptr) {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     return -1;
    // }
    //
    // if (!window.InitGlew())
    //     return -1;
    //
    // Renderer renderer;
    //
    // Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    // customShader.use();
    //
    // while (!glfwWindowShouldClose(window.instance)) {
    //     window.processInput();
    //
    //     renderer.Render();
    //
    //     window.updateDisplay();
    // }
    // return 0;
}

