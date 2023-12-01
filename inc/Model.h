#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Material.h"
#include "Mesh.h"
#include "math.h"
#include "ObjParser.h"
#include "settings.h"
#include "Texture.h"
#include "utils.h"

enum Model_KeyBinds {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    FORWARD,
    BACKWARD,
    X_ROT,
    X_ROT_INV,
    Y_ROT,
    Y_ROT_INV,
    Z_ROT,
    Z_ROT_INV,
};

class Model {
 public:
     void loadObjFile(const std::string& inputFile);
     void loadTexture(const char* texturePath);

     void draw(Shader& shader, float deltaTime);
     void bindDefaultTexture() const;
     GLuint getTextureId() const;

     void processKeyboardInput(Model_KeyBinds input, float deltaTime);
     void resetTransform();

     void switchTexture();
     void switchPolygonMode();
     void switchTextureMode();
     void switchTextureMapping();
     void toggleAutoRotation();

 private:
     std::unique_ptr<Mesh> mesh = nullptr;
     std::vector<Texture> textures;
     size_t textureIndex = 0;

     Material material;

     float textureTransitionFactor = 0.0f;
     bool polygonMode = false;
     bool useTexture = false;
     bool mappingMethod = false;
     bool autoRotation = true;
};

#endif  // INC_MODEL_H_
