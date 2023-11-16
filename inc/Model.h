#ifndef INC_MODEL_H_
#define INC_MODEL_H_

#include <iostream>
#include "./Mesh.h"

class Model {
 public:
     Model(const std::string& inputFile);
     void draw(Shader& shader, double currentTime) const;

 // private:
     Mesh mesh;
};

#endif  // INC_MODEL_H_
