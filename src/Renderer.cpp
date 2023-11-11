#include "../inc/Renderer.h"

Renderer::Renderer() {
	float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    // Todo: check for errors
	// glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

void Renderer::Render(Shader& shader) {
	Vec3f cubePositions[] = {
		Vec3f(0.0f, 0.0f, -5.0f),
		Vec3f(2.0f,  5.0f, -15.0f),
		Vec3f(-1.5f, -2.2f, -2.5f),
		Vec3f(-3.8f, -2.0f, -12.3f),
		Vec3f(2.4f, -0.4f, -3.5f),
		Vec3f(-1.7f,  3.0f, -7.5f),
		Vec3f(1.3f, -2.0f, -2.5f),
		Vec3f(1.5f,  2.0f, -2.5f),
		Vec3f(1.5f,  0.2f, -1.5f),
		Vec3f(-1.3f,  1.0f, -1.5f)
    };
 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 10; i++) {
		Mat4f model(1.0f);
		model = Mat4f::translate(model, cubePositions[i]);

		float angle = i * glfwGetTime();
		model = Mat4f::rotate(model, math::radians(angle), Vec3f(1.0f, 0.0f, 0.0f));
        model = Mat4f::transpose(model);
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
