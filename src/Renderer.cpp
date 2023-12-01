#include "Renderer.h"
#include "settings.h"

void Renderer::loadShader() {
    glGenVertexArrays(1, &this->lightVao);
    // glGenBuffers(1, &this->lightVbo);

    glBindVertexArray(this->lightVao);

    // glBindBuffer(GL_ARRAY_BUFFER, this->lightVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), nullptr);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    this->shader.compileProgram("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader.use();
    this->shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    this->shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    this->shader.setVec3("lightPos", 3.0f, 10.0f, -5.0f);
    // this->shader.setVec3("viewPos", CAM_START_POSITION.x, CAM_START_POSITION.y, CAM_START_POSITION.z);
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

