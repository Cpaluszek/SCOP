#include "../inc/Model.h"

#define COMMENT_KEYWORD "#"
#define VERTEX_KEYWORD "v"
#define FACE_KEYWORD "f"
#define SMOOTH_SHADING_KEYWORD "s"
#define OBJ_NAME_KEYWORD "o"
#define GROUP_NAME_KEYWORD "g"
#define LINE_KEYWORD "l"
#define TEXT_COORDS_KEYWORD "vt"
#define VERTEX_NOMALS_KEYWORD "vn"
#define MAT_FILE_KEYWORD "mtllib"
#define MAT_NAME_KEYWORD "usemtl"

Model::~Model() {
    delete mesh;
}

Model::Model(const std::string& inputFile) {
    std::ifstream objFile(inputFile, std::ios::in);
    if (!objFile.is_open()) {
        throw std::runtime_error("Could not open input file '" + inputFile + "'!");
    }

    try {
        this->parseOBJFile(objFile);
        objFile.close();
    } catch (const std::exception& e){
        objFile.close();
        throw;
    }
}

void Model::draw(Shader& shader, double currentTime) const {
    this->mesh->draw(shader, currentTime);
}


// [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
void Model::parseOBJFile(std::ifstream& file){
    // Setup random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    std::vector<Vertex> parsedVertices;
    std::vector<Vertex> finalVertices;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue ;
        }

        std::vector<std::string> lineSplit = utils::splitString(line, ' ');
        if (lineSplit.size() == 1 || lineSplit[0] == COMMENT_KEYWORD) {
            continue ;
        }

        if (lineSplit[0] == VERTEX_KEYWORD) {
            if (lineSplit.size() < 4 || lineSplit.size() > 5) {
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
                throw std::runtime_error("Argument is invalid: " + line);
            } catch (const std::out_of_range &e) {
                throw std::runtime_error("Argument is out of range:" + line);
            }
        } else if (lineSplit[0] == FACE_KEYWORD) {
            if (parsedVertices.size() == 0) {
                throw std::runtime_error("Incorrect file format: need vertices to specify faces");
            }
            if (lineSplit.size() < 4 || lineSplit.size() > 5) {
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
                throw std::runtime_error("Argument is invalid: " + line);
            } catch (const std::out_of_range &e) {
                throw std::runtime_error("Argument is out of range: " + line);
            }
        }
        // Todo: check for other keywords
        else if (lineSplit[0] == SMOOTH_SHADING_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == OBJ_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == GROUP_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == LINE_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == TEXT_COORDS_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == VERTEX_NOMALS_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == MAT_FILE_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == MAT_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else {
            std::cerr << "Parsing: '" << line << "' unknown keyword" << std::endl;
        }
    }
    this->mesh = new Mesh(finalVertices);
}
