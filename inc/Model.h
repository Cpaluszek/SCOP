#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <random>
#include <vector>
#include "./Mesh.h"
#include "./utils.h"

typedef std::vector<Vertex> VertexVector;

class Model {
 public:
     ~Model();
     Model(const std::string& inputFile);
     void draw(Shader& shader, double currentTime) const;

 private:
     Mesh* mesh;

     void loadOBJFile(std::ifstream& file);
     void parseVertex(
             VertexVector& parsedVertices,
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
