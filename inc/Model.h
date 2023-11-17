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

class Model {
 public:
     ~Model();
     Model(const std::string& inputFile);
     void draw(Shader& shader, double currentTime) const;

 private:
     Mesh* mesh;
};

#endif  // INC_MODEL_H_
