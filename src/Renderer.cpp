#include "../inc/Renderer.h"
#include <GL/gl.h>

Renderer::Renderer(Camera const& camera): camera(camera) {}

void Renderer::loadShader() {
   // Todo: check for errors
    glEnable(GL_DEPTH_TEST);
    // Todo: check for shader compilation error
    this->shader.compileProgram("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader.use();
}

void Renderer::render(Model& model, float deltaTime) {
   // Todo: check for errors
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTextureId());

    // Set view matrix
    Mat4f view = camera.getViewMatrix();
    view = Mat4f::transpose(view);
    this->shader.setMat4("view", view);

    // Todo: if projection is static remove of the main loop
    // Set projection matrix
    Mat4f projection = camera.getProjectionMatrix();
    projection = Mat4f::transpose(projection);
    this->shader.setMat4("projection", projection);
    
    /////////////////////////////////////
    model.draw(this->shader, glfwGetTime(), deltaTime);
}

