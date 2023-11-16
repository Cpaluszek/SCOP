#include "../inc/Model.h"
#include <stdexcept>

// [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
// o [object name]
// ...
//  g [group name]
//  ...
//
// mtllib [external .mtl file format] -> Reference materials
// usmtl [material name] -> material name specified in .mtl file
//
// s off -> smooth shading
//
// v x y z [w] -> vertex position (w) is optionnal - default to 1.0
//
// f v1 v2 v3 ... -> faces elements (start at 1) - -1 refers to the last

// Todo: order matter
// v -> f
Model::Model(const std::string& inputFile) {
    std::ifstream objFile(inputFile, std::ios::in);
    if (!objFile.is_open()) {
        throw std::runtime_error("Could not open input file '" + inputFile + "'!");
    }
    std::string line;
    std::vector<Vertex> parsedVertices;
    std::vector<unsigned int> parsedIndices;

    while (std::getline(objFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        } else if (line[0] == 'v') {
            std::istringstream iss(line);

            char v;
            iss >> v;

            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            parsedVertices.push_back(vertex);
        } else if (line[0] == 'f') {
            char f;

            std::istringstream iss(line);
            iss >> f;

            int num;
            int count = 0;
            while (iss >> num) {
                // Todo: if num is negative
                if (count++ == 3) {
                    int a = *(parsedIndices.rbegin() + 3 - 1);
                    int b = *(parsedIndices.rbegin() + 1 - 1);
                    parsedIndices.push_back(a);
                    parsedIndices.push_back(b);
                }
                parsedIndices.push_back(num - 1); 
            }
            
        }
    }
    objFile.close();
    this->mesh = Mesh(parsedVertices, parsedIndices);

    /////////////////////////////
    // DO NOT TOUCH THIS!
    this->mesh.setupMesh();
    /////////////////////////////
}

void Model::draw(Shader& shader, double currentTime) const {
    this->mesh.draw(shader, currentTime);
}

