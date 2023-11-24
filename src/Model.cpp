#include "Model.h"

void Model::loadObjFile(const std::string& inputFile) {
    ObjParser parser;

    try {
        parser.parseObjFile(inputFile);
    } catch (const std::exception& e){
        throw;
    }
    this->useSmoothShading = parser.useSmoothShading;
    this->mesh = std::make_unique<Mesh>(parser.finalVertices);
}

void Model::loadTexture(const char* texturePath) {
    this->texture.loadTextureFile(texturePath);
}

GLuint Model::getTextureId() const {
    return this->texture.id;
}

void Model::switchPolygonMode() {
    this->polygonMode ^= true;
    glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode ? GL_LINE : GL_FILL);
}
void Model::switchTextureMode() {
    this->useTexture ^= true;
}

void Model::draw(Shader& shader, double currentTime, float deltaTime) {
    if (this->useTexture && this->textureTransitionFactor < 1.0f) {
        this->textureTransitionFactor = std::min(this->textureTransitionFactor + deltaTime, 1.0f);
    } else if (!this->useTexture && this->textureTransitionFactor > 0.0f) {
        this->textureTransitionFactor = std::max(this->textureTransitionFactor - deltaTime, 0.0f);
    }
    shader.setFloat("textureTransitionFactor", this->textureTransitionFactor);

    this->mesh->draw(shader, currentTime);
}

void Model::processKeyboardInput(Model_Movement direction, float deltaTime) {
    float velocity = MOVEMENT_SPEED * deltaTime;

    if (direction == UP) {
        this->mesh->position.y += velocity;
    } else if (direction == DOWN) {
        this->mesh->position.y -= velocity;
    } else if (direction == LEFT) {
        this->mesh->position.x -= velocity;
    } else if (direction == RIGHT) {
        this->mesh->position.x += velocity;
    } else if (direction == FORWARD) {
        this->mesh->position.z -= velocity;
    } else if (direction == BACKWARD) {
        this->mesh->position.z += velocity;
    }
}

void Model::resetPosition() {
    this->mesh->position = Vec3f();
}
