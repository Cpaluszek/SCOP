#include "Renderer.h"
#include "Camera.h"
#include "settings.h"

void Renderer::loadShader() {
    glGenVertexArrays(1, &this->lightVao);

    glBindVertexArray(this->lightVao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), nullptr);
    glEnableVertexAttribArray(0);

    // Face culling
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    // Depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    // Anti aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    this->shader.compileProgram("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader.use();

    Vec3f lightPos = Vec3f(-5.0f, 10.0f, 0.0f);
    this->shader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
    this->shader.setVec3("viewPos", CAM_START_POSITION.x, CAM_START_POSITION.y, CAM_START_POSITION.z);
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

