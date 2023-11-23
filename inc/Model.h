#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <vector>
#include "./Mesh.h"
#include "./math.h"
#include "./ObjParser.h"
#include "./Texture.h"
#include "./utils.h"

enum Model_Movement {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    FORWARD,
    BACKWARD
};

const float MOVEMENT_SPEED = 1.5f;

class Model {
 public:
     void loadObjFile(const std::string& inputFile);
     void loadTexture(const char* texturePath);

     void draw(Shader& shader, double currentTime, float deltaTime);

     void processKeyboardInput(Model_Movement direction, float deltaTime);
     void resetPosition();

     GLuint getTextureId() const;

     bool useTexture = false;
     bool polygonMode = false;

 private:
     std::unique_ptr<Mesh> mesh;
     Texture texture;

     bool useSmoothShading = false;     // Todo: use in shaders
     float textureTransitionFactor = 0.0f;
};

#endif  // INC_MODEL_H_
