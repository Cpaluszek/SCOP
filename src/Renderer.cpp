#include "Renderer.h"
#include "settings.h"

void Renderer::loadShader() {
    glGenVertexArrays(1, &this->lightVao);

    glBindVertexArray(this->lightVao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), nullptr);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    this->shader.compileProgram("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader.use();
    // Todo: fix this mess
    // Note: create Light class?
    this->shader.setVec3("lightPos", 3.0f, 10.0f, -5.0f);
    Vec3f lightPos = Vec3f(-5.0f, 10.0f, 0.0f);
    this->shader.setVec3("viewPos", lightPos.x, lightPos.y, lightPos.z);
}

void Renderer::render(const Camera& camera, Model& model, float deltaTime) {
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view matrix
    Mat4f view = Mat4f::transpose(camera.getViewMatrix());
    this->shader.setMat4("view", view);

    // Set projection matrix
    Mat4f projection = Mat4f::transpose(camera.getProjectionMatrix());
    this->shader.setMat4("projection", projection);
    
    model.draw(this->shader, deltaTime);
}

