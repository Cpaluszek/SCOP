#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <random>
#include <vector>
#include "./Mesh.h"
#include "./math.h"
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

     void loadOBJFile(std::ifstream& file);
     void parseVertex(
             VertexVector& parsedVertices,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseVertexNormal(
             VertexVector& parsedVertices,
             size_t& normalCount,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseFace(
             const VertexVector& parsedVertices,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
};

#endif  // INC_MODEL_H_
