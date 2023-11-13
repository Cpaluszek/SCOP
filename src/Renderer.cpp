#include "../inc/Renderer.h"

Renderer::Renderer(Camera const& camera): camera(camera) {
    // Todo: check for errors

    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glEnableVertexAttribArray(0);

    // Todo: protect new Shader -> static reference may be better

    // Init shader program
    this->shader = new Shader("./shader/vertex.glsl", "./shader/fragment.glsl");
    this->shader->use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);

    delete this->shader;
}

// Todo: use const str or define for shader parameter name
void Renderer::render(Mesh const &mesh) {

    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view matrix
    Mat4f view = camera.getViewMatrix();
    view = Mat4f::transpose(view);
    this->shader->setMat4("view", view);

    // Set projection matrix
    Mat4f projection = Mat4f::perspective(math::radians(camera.zoom),
            ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
    projection = Mat4f::transpose(projection);
    this->shader->setMat4("projection", projection);

    Mat4f identity(1.0f);
    double currentTime = glfwGetTime();

    Mat4f model = Mat4f::translate(identity, mesh.position);

    float angle = math::radians(6.0f * currentTime);
    model = Mat4f::rotate(model, angle, Vec3f(1.0f, 0.0f, 0.0f));
    model = Mat4f::transpose(model);
    this->shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
}

void Renderer::BindMeshData(Mesh const& mesh) {
    glBufferData(
            GL_ARRAY_BUFFER,
            mesh.vertices.size() * sizeof(Vertex),
            mesh.vertices.data(),
            GL_STATIC_DRAW);
    //Note: GL_DYNAMIC_DRAW ??

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

}
