#include "../inc/Renderer.h"

Renderer::Renderer(Camera const& camera): camera(camera) {
    // Todo: check for errors

    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_GEQUAL);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Todo: protect new Shader -> static? reference may be better

    // Init shader program
    this->shader = new Shader("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader->use();
}

Renderer::~Renderer() {
    delete this->shader;
}

void Renderer::render(const Model* model) const {
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view matrix
    Mat4f view = camera.getViewMatrix();
    view = Mat4f::transpose(view);
    this->shader->setMat4("view", view);

    // Set projection matrix
    Mat4f projection = Mat4f::perspective(
            math::radians(camera.zoom),
            ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
    projection = Mat4f::transpose(projection);
    this->shader->setMat4("projection", projection);
    
    /////////////////////////////////////
    model->draw(*this->shader, glfwGetTime());
}

