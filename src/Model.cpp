#include "../inc/Model.h"
#include <stdexcept>
#include <vector>

Model::~Model() {
    delete mesh;
}

// Todo: move parsing to another file

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

    std::vector<Vertex> parsedVertices;
    std::vector<Vertex> finalVertices;

    std::string line;
    while (std::getline(objFile, line)) {
        if (line.empty()) {
            continue ;
        }

        std::vector<std::string> lineSplit = utils::splitString(line, ' ');
        if (lineSplit.size() == 1 || lineSplit[0] == COMMENT_KEYWORD) {
            continue ;
        }

        if (lineSplit[0] == VERTEX_KEYWORD) {
            if (lineSplit.size() < 4 || lineSplit.size() > 5) {
                objFile.close();
                throw std::runtime_error("Incorrect vertex format: (x, y, z, [w])");
            }

            try {
                Vertex vertex {
                    std::stof(lineSplit[1]),
                    std::stof(lineSplit[2]), 
                    std::stof(lineSplit[3]),
                    0.0f, 0.0f, 0.0f
                };
                parsedVertices.push_back(vertex);
             } catch (const std::invalid_argument &e) {
                objFile.close();
                throw std::runtime_error("Argument is invalid: " + line);
            } catch (const std::out_of_range &e) {
                objFile.close();
                throw std::runtime_error("Argument is out of range:" + line);
            }
        } else if (lineSplit[0] == FACE_KEYWORD) {
            if (lineSplit.size() < 4 || lineSplit.size() > 5) {
                objFile.close();
                throw std::runtime_error("Incorrect face format: should be triangle or quad");
            }
            Vec3f randomColor(dis(gen), dis(gen), dis(gen));

            try {
                for (size_t i = 1; i < lineSplit.size(); i++) {
                    int index = std::stoi(lineSplit[i]);
                    // Todo: check for neg or overflow
                    if (i == 4) {
                        auto a = *(finalVertices.rbegin() + 3 - 1);
                        auto b = *(finalVertices.rbegin() + 1 - 1);
                        a.r = randomColor.x;
                        a.g = randomColor.y;
                        a.b = randomColor.z;
                        finalVertices.push_back(a);
                        b.r = randomColor.x;
                        b.g = randomColor.y;
                        b.b = randomColor.z;
                        finalVertices.push_back(b);
                    }
                    auto currentVertex = parsedVertices[index - 1];
                    currentVertex.r = randomColor.x;
                    currentVertex.g = randomColor.y;
                    currentVertex.b = randomColor.z;
                    finalVertices.push_back(currentVertex);
                }
            } catch (const std::invalid_argument &e) {
                objFile.close();
                throw std::runtime_error("Argument is invalid: " + line);
            } catch (const std::out_of_range &e) {
                objFile.close();
                throw std::runtime_error("Argument is out of range: " + line);
            }
        }
    }

    objFile.close();
    this->mesh = new Mesh(finalVertices);
}

void Model::draw(Shader& shader, double currentTime) const {
    this->mesh->draw(shader, currentTime);
}

