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
#include "./settings.h"
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

class Model {
 public:
     void loadObjFile(const std::string& inputFile);
     void loadTexture(const char* texturePath);

     void draw(Shader& shader, double currentTime, float deltaTime);

     void processKeyboardInput(Model_Movement direction, float deltaTime);
     void resetPosition();

     GLuint getTextureId() const;
     void switchPolygonMode();
     void switchTextureMode();

 private:
     std::unique_ptr<Mesh> mesh;
     Texture texture;

     float textureTransitionFactor = 0.0f;
     bool useSmoothShading = false;     // Todo: use in shaders
     bool polygonMode = false;
     bool useTexture = false;
};

#endif  // INC_MODEL_H_
