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

enum Face_Format {
    VERTEX,
    VERTEX_TEXTURE,
    VERTEX_TEXTURE_NORMAL,
    VERTEX_NORMAL
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

     Face_Format faceFormat = VERTEX;
     bool useSmoothShading = false;     // Todo: use in shaders

     void loadOBJFile(std::ifstream& file);
     void parseVertex(
             VertexVector& parsedVertices,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseVertexNormal(
             std::vector<Vec3f>& normals,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseVertexTextureCoords(
             std::vector<Vec3f>& textureCoords,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseFace(
             const VertexVector& parsedVertices,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseFaceTexture(
             const VertexVector& parsedVertices,
             std::vector<Vec3f>& textureCoords,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseFaceTextureNormal(
             const VertexVector& parsedVertices,
             std::vector<Vec3f>& textureCoords,
             std::vector<Vec3f>& normals,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void parseFaceNormal(
             const VertexVector& parsedVertices,
             std::vector<Vec3f>& normals,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line);
     void determineFaceFormat(const std::vector<std::string>& lineSplit);
};

#endif  // INC_MODEL_H_
