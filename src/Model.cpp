#include "Model.h"

void Model::loadObjFile(const std::string& inputFile) {
    ObjParser parser;

    try {
        parser.parseObjFile(inputFile);
    } catch (const std::exception& e){
        throw;
    }
    this->useSmoothShading = parser.useSmoothShading;
    this->material = parser.material;

    this->mesh = std::make_unique<Mesh>(parser.finalVertices, parser.vertexFormat);

    std::cout << this->material << std::endl;
}

void Model::bindDefaultTexture() const {
    this->textures.at(this->textureIndex).bind();
}

GLuint Model::getTextureId() const {
    return this->textures.at(this->textureIndex).id;
}

void Model::loadTexture(const char* texturePath) {
    Texture texture;
    texture.loadTextureFile(texturePath);
    this->textures.push_back(texture);
}

void Model::switchTexture() {
    this->textureIndex = (this->textureIndex + 1) % this->textures.size();
    this->textures.at(this->textureIndex).bind();
}

void Model::switchPolygonMode() {
    this->polygonMode ^= true;
    glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode ? GL_LINE : GL_FILL);
}

void Model::switchTextureMode() {
    this->useTexture ^= true;
}

void Model::processKeyboardInput(Model_KeyBinds input, float deltaTime) {
    float velocity = MOVEMENT_SPEED * deltaTime;

    // Translations
    if (input == UP) {
        this->mesh->position.y += velocity;
    } else if (input == DOWN) {
        this->mesh->position.y -= velocity;
    } else if (input == LEFT) {
        this->mesh->position.x -= velocity;
    } else if (input == RIGHT) {
        this->mesh->position.x += velocity;
    } else if (input == FORWARD) {
        this->mesh->position.z += velocity;
    } else if (input == BACKWARD) {
        this->mesh->position.z -= velocity;
    }
    // Rotations
    if (input == X_ROT) {
        this->mesh->rotation.x += ROTATION_SPEED * deltaTime;
    } else if (input == X_ROT_INV) {
        this->mesh->rotation.x -= ROTATION_SPEED * deltaTime;
    } else if (input == Y_ROT) {
        this->mesh->rotation.y += ROTATION_SPEED * deltaTime;
    } else if (input == Y_ROT_INV) {
        this->mesh->rotation.y -= ROTATION_SPEED * deltaTime;
    } else if (input == Z_ROT) {
        this->mesh->rotation.z += ROTATION_SPEED * deltaTime;
    } else if (input == Z_ROT_INV) {
        this->mesh->rotation.z -= ROTATION_SPEED * deltaTime;
    }
}

void Model::resetTransform() {
    this->mesh->resetTransform();
}

void Model::toggleAutoRotation() {
    this->autoRotation ^= true;
}

void Model::draw(Shader& shader, float deltaTime) {
    if (this->useTexture && this->textureTransitionFactor < 1.0f) {
        this->textureTransitionFactor = std::min(this->textureTransitionFactor + deltaTime, 1.0f);
    } else if (!this->useTexture && this->textureTransitionFactor > 0.0f) {
        this->textureTransitionFactor = std::max(this->textureTransitionFactor - deltaTime, 0.0f);
    }
    shader.setFloat("textureTransitionFactor", this->textureTransitionFactor);

    if (this->autoRotation) {
        this->mesh->rotation.y += ROTATION_SPEED * deltaTime;
    }
    this->mesh->draw(shader);
}

