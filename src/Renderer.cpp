#include "Renderer.h"
#include "settings.h"

void Renderer::loadShader() {
    glEnable(GL_DEPTH_TEST);
    // Todo: check for shader compilation error
    this->shader.compileProgram("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader.use();
}

void Renderer::render(const Camera& camera, Model& model, float deltaTime) {
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
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
    
    model.draw(this->shader, deltaTime);
}

