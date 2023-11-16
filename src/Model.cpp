#include "../inc/Model.h"

Model::Model() {
    this->mesh = Mesh();
}

void Model::draw(Shader& shader, double currentTime) const {
    this->mesh.draw(shader, currentTime);
}

