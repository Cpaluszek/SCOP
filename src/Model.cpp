#include "../inc/Model.h"
#include <cstdlib>
#include <random>
#include <stdexcept>

Model::~Model() {
    delete mesh;
}

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
    // Setup random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);



    std::ifstream objFile(inputFile, std::ios::in);
    if (!objFile.is_open()) {
        throw std::runtime_error("Could not open input file '" + inputFile + "'!");
    }
    std::string line;
    std::vector<Vertex> parsedVertices;
    std::vector<GLuint> parsedIndices;

    std::vector<Vertex> finalVertices;

    while (std::getline(objFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        if (line[0] == 'v') {
            std::istringstream iss(line);

            char v;
            iss >> v;

            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            parsedVertices.push_back(vertex);
        } else if (line[0] == 'f') {
            Vec3f randomColor(dis(gen), dis(gen), dis(gen));

            char f;

            std::istringstream iss(line);
            iss >> f;

            int num;
            int count = 0;
            while (iss >> num) {
                // Todo: if num is negative
                
                // Todo: clean trash code
                if (count++ == 3) {
                    int a = *(parsedIndices.rbegin() + 3 - 1);
                    int b = *(parsedIndices.rbegin() + 1 - 1);
                    parsedIndices.push_back(a);
                    parsedIndices.push_back(b);
                    auto currentVertex = parsedVertices[a];
                    currentVertex.r = randomColor.x;
                    currentVertex.g = randomColor.y;
                    currentVertex.b = randomColor.z;
                    finalVertices.push_back(currentVertex);

                    currentVertex = parsedVertices[b];
                    currentVertex.r = randomColor.x;
                    currentVertex.g = randomColor.y;
                    currentVertex.b = randomColor.z;
                    finalVertices.push_back(currentVertex);
                }
                parsedIndices.push_back(num - 1);
                
                auto currentVertex = parsedVertices[num - 1];
                currentVertex.r = randomColor.x;
                currentVertex.g = randomColor.y;
                currentVertex.b = randomColor.z;
                finalVertices.push_back(currentVertex);
            }
        }
    }

    objFile.close();
    this->mesh = new Mesh(finalVertices);
}

void Model::draw(Shader& shader, double currentTime) const {
    this->mesh->draw(shader, currentTime);
}

