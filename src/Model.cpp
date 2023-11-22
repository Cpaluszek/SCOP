#include "../inc/Model.h"

Model::~Model() {
    delete mesh;
}

Model::Model(const std::string& inputFile) {
    std::ifstream objFile(inputFile, std::ios::in);
    if (!objFile.is_open()) {
        throw std::runtime_error("Could not open input file '" + inputFile + "'!");
    }

    ObjParser parser;

    try {
        parser.parseObjFile(objFile);
        objFile.close();
    } catch (const std::exception& e){
        objFile.close();
        throw;
    }
    this->useSmoothShading = parser.useSmoothShading;
    this->mesh = new Mesh(parser.finalVertices);
}

void Model::loadTexture(const char* texturePath) {
    this->texture.loadTextureFile(texturePath);
}

GLuint Model::getTextureId() const {
    return this->texture.id;
}

void Model::draw(Shader& shader, double currentTime, float deltaTime) {
    // Todo: use events / callback
    glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode ? GL_LINE : GL_FILL);

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
