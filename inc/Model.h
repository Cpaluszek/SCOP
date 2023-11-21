#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "./Mesh.h"
#include "./math.h"
#include "./ObjParser.h"
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
     ~Model();
     Model(const std::string& inputFile);
     void draw(Shader& shader, double currentTime, float deltaTime);

     void processKeyboardInput(Model_Movement direction, float deltaTime);

     bool useTexture = false;
     bool polygonMode = false;
     float textureTransitionFactor = 0.0f;

 private:
     Mesh* mesh;

     bool useSmoothShading = false;     // Todo: use in shaders
};

#endif  // INC_MODEL_H_
