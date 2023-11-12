#include "../inc/Renderer.h"
#include "glfw3.h"

Renderer::Renderer(Camera& camera): camera(camera) {
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

	glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

	// Todo: protect new Shader -> static reference may be better

	// Init shader program
	this->shader = new Shader("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader->use();

	// Set projection matrix
	Mat4f projection = Mat4f::perspective(math::radians(camera.zoom), 
				800.0f / 600.0f, NEAR_CLIP, FAR_CLIP);
    projection = Mat4f::transpose(projection);
	this->shader->setMat4("projection", projection);
	
	// Set view matrix
	Mat4f view = camera.getViewMatrix();
    view = Mat4f::transpose(view);
	this->shader->setMat4("view", view);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);

	delete this->shader;
}

void Renderer::render() {
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4f identity(1.0f);
	double currentTime = glfwGetTime();

	for (int i = 0; i < 10; i++) {
		Mat4f model = Mat4f::translate(identity, cubePositions[i]);

		float angle = i * currentTime;
		model = Mat4f::rotate(model, math::radians(angle), Vec3f(1.0f, 0.0f, 0.0f));
        model = Mat4f::transpose(model);
		this->shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
