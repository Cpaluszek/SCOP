#include <iostream>

#include "../inc/Shader.h"
#include "../inc/Window.h"

void processInput(GLFWwindow *window);

// Todo: stb_image.h authorized?

int main() {
    Window window;

    if (window.instance == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

	if (!window.InitGlew()) {
		return -1;
	}

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    Shader customShader("./shader/vertex.glsl", "./shader/fragment.glsl");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window.instance)) {
        window.processInput();

        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        customShader.use();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.instance);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}

