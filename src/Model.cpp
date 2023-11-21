#include "../inc/Model.h"
#include <stdexcept>
#include <vector>

#define COMMENT_KEYWORD "#"
#define VERTEX_KEYWORD "v"
#define FACE_KEYWORD "f"
#define SMOOTH_SHADING_KEYWORD "s"
#define OBJ_NAME_KEYWORD "o"
#define GROUP_NAME_KEYWORD "g"
#define LINE_KEYWORD "l"
#define TEXT_COORDS_KEYWORD "vt"
#define VERTEX_NORMALS_KEYWORD "vn"
#define PARAM_SPACE_VERTICES_KEYWORD "vn"
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
        this->loadOBJFile(objFile);
        objFile.close();
    } catch (const std::exception& e){
        objFile.close();
        throw;
    }
}

void Model::draw(Shader& shader, double currentTime, float deltaTime) {
    // Todo: use events / callback
    glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode ? GL_LINE : GL_FILL);

    if (this->useTexture && this->textureTransitionFactor < 1.0f) {
        this->textureTransitionFactor = std::min(this->textureTransitionFactor + deltaTime, 1.0f);
    } else if (!this->useTexture && this->textureTransitionFactor > 0.0f) {
        this->textureTransitionFactor = std::max(this->textureTransitionFactor - deltaTime, 0.0f);
    }
    shader.setFloat("textureTransitionFactor", this->textureTransitionFactor);

    this->mesh->draw(shader, currentTime);
}

void Model::processKeyboardInput(Model_Movement direction, float deltaTime) {
    float velocity = MOVEMENT_SPEED * deltaTime;

    if (direction == UP) {
        this->mesh->position.y += velocity;
    } else if (direction == DOWN) {
        this->mesh->position.y -= velocity;
    } else if (direction == LEFT) {
        this->mesh->position.x -= velocity;
    } else if (direction == RIGHT) {
        this->mesh->position.x += velocity;
    } else if (direction == FORWARD) {
        this->mesh->position.z -= velocity;
    } else if (direction == BACKWARD) {
        this->mesh->position.z += velocity;
    }
}

// [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
void Model::loadOBJFile(std::ifstream& file) {
    // TODO: move to another file
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    std::vector<Vec3f> normals;
    std::vector<Vec3f> textureCoords;
    VertexVector parsedVertices;
    VertexVector finalVertices;

    std::string line;
    while (std::getline(file, line)) {
        // Todo: check for other keywords
        // How to process invalid or unsupported keyword - exit??
        if (line.empty()) continue ;

        std::vector<std::string> lineSplit = utils::splitString(line, ' ');
        if (lineSplit.size() == 1 || lineSplit[0] == COMMENT_KEYWORD) continue ;

        // Note: maybe use map with functions to iterate
        if (lineSplit[0] == VERTEX_KEYWORD) {
            if (finalVertices.size() != 0) {
                throw std::runtime_error("Vertex to need be listed before faces");
            }
            this->parseVertex(parsedVertices, lineSplit, line);
        } else if (lineSplit[0] == FACE_KEYWORD) {
            if (parsedVertices.size() == 0) {
                throw std::runtime_error("Vertex need be listed before faces");
            } else if (finalVertices.size() == 0) {
                this->determineFaceFormat(lineSplit);
            } else if (lineSplit.size() < 4 || lineSplit.size() > 5) {
                throw std::runtime_error("Incorrect face format: should be triangle or quad");
            }
    
            Vec3f randomColor(dis(gen), dis(gen), dis(gen));
            switch (this->faceFormat) {
                case VERTEX:
                    this->parseFace(parsedVertices, finalVertices, randomColor, lineSplit, line);
                    break;
                case VERTEX_TEXTURE:
                    this->parseFaceTexture(parsedVertices, textureCoords, finalVertices, randomColor, lineSplit, line);
                    break;
                case VERTEX_TEXTURE_NORMAL:
                    this->parseFaceTextureNormal(parsedVertices, textureCoords, normals, finalVertices, randomColor, lineSplit, line);
                    break;
                case VERTEX_NORMAL:
                    this->parseFaceNormal(parsedVertices, normals, finalVertices, randomColor, lineSplit, line);
                    break;
            }
        }
        else if (lineSplit[0] == VERTEX_NORMALS_KEYWORD) {
            this->parseVertexNormal(normals, lineSplit, line);
        } else if (lineSplit[0] == SMOOTH_SHADING_KEYWORD) {
            if (lineSplit.size() != 2) {
                throw std::runtime_error("Incorrect smooth shading format: (1 / off)");
            }
            if (lineSplit[1] == "1") this->useSmoothShading = true;
            else if (lineSplit[1] == "off") this->useSmoothShading = false;
            else throw std::runtime_error("Incorrect smooth shading parameter: " + lineSplit[1]);
        } else if (lineSplit[0] == TEXT_COORDS_KEYWORD) {
            this->parseVertexTextureCoords(textureCoords, lineSplit, line);
        } else if (lineSplit[0] == MAT_FILE_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == MAT_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == OBJ_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == GROUP_NAME_KEYWORD) {
            std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
        } else if (lineSplit[0] == LINE_KEYWORD) {
            std::cerr << "This project does not support line elements" << std::endl;
        } else if (lineSplit[0] == PARAM_SPACE_VERTICES_KEYWORD) {
            std::cerr << "This project does not support parameter space vertices" << std::endl;
        } else {
            std::cerr << "Parsing: '" << line << "' unknown keyword" << std::endl;
        }
    }
    this->mesh = new Mesh(finalVertices);
}

void Model::parseVertex(
        VertexVector& parsedVertices,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {
    if (lineSplit.size() < 4 || lineSplit.size() > 5) {
        throw std::runtime_error("Incorrect vertex format: (x, y, z, [w])");
    }

    try {
        GLfloat x = std::stof(lineSplit[1]);
        GLfloat y = std::stof(lineSplit[2]);
        GLfloat z = std::stof(lineSplit[3]);
        Vertex vertex {
            Vec3f(x, y, z),
            Vec3f(),
            Vec3f(),
            x, y
            
        };
        parsedVertices.push_back(vertex);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range:" + line);
    }
}

void Model::parseVertexNormal(
        std::vector<Vec3f>& normals,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {

    if (lineSplit.size() != 4) {
        throw std::runtime_error("Incorrect vertex normal format: (x, y, z)");
    }

    try {
        GLfloat x = std::stof(lineSplit[1]);
        GLfloat y = std::stof(lineSplit[2]);
        GLfloat z = std::stof(lineSplit[3]);
        Vec3f normal(x, y, z);
        normals.push_back(Vec3f::normalize(normal));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void Model::parseVertexTextureCoords(
        std::vector<Vec3f>& textureCoords,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {

    if (lineSplit.size() < 2 || lineSplit.size() > 4) {
        throw std::runtime_error("Incorrect vertex texture coords format: (u, [v, w])");
    }

    try {
        GLfloat u = std::stof(lineSplit[1]);
        GLfloat v = lineSplit.size() > 2 ? std::stof(lineSplit[2]) : 0.0f;
        if (u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f) {
            throw std::runtime_error("Texture coords should in range [0.0f, 1.0f]");
        }
        textureCoords.push_back(Vec3f(u, v, 0.0f));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void Model::parseFace(
             const VertexVector& parsedVertices,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line) {
    try {
        for (size_t i = 1; i < lineSplit.size(); i++) {

            size_t slashPos = lineSplit[i].find('/');
            if (slashPos != std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }

            int index = std::stoi(lineSplit[i]);
            // Todo: check for neg or overflow
            if (i == 4) {
                auto a = *(finalVertices.rbegin() + 3 - 1);
                auto b = *(finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                finalVertices.push_back(a);
                b.color = faceColor;
                finalVertices.push_back(b);
            }
            auto currentVertex = parsedVertices[index - 1];
            currentVertex.color = faceColor;
            finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

// Todo: test
void Model::parseFaceTexture(
        const VertexVector& parsedVertices,
        std::vector<Vec3f>& textureCoords,
        VertexVector& finalVertices,
        const Vec3f& faceColor,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {
    try {
        for (size_t i = 1; i < lineSplit.size(); i++) {

            size_t slashPos = lineSplit[i].find('/');
            if (slashPos == std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }
            std::vector<std::string> indices = utils::splitString(lineSplit[i], '/');
            if (indices.size() != 2) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices[0]);
            int textCoordIndex = std::stoi(indices[1]);
            // Todo: check for neg or overflow
            if (i == 4) {
                auto a = *(finalVertices.rbegin() + 3 - 1);
                auto b = *(finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                finalVertices.push_back(a);
                b.color = faceColor;
                finalVertices.push_back(b);
            }
            auto currentVertex = parsedVertices[vertexIndex - 1];
            currentVertex.textX = textureCoords[textCoordIndex - 1].x;
            currentVertex.textY = textureCoords[textCoordIndex - 1].y;
            currentVertex.color = faceColor;
            finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void Model::parseFaceTextureNormal(
        const VertexVector& parsedVertices,
        std::vector<Vec3f>& textureCoords,
        std::vector<Vec3f>& normals,
        VertexVector& finalVertices,
        const Vec3f& faceColor,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {
    try {
        for (size_t i = 1; i < lineSplit.size(); i++) {

            size_t slashPos = lineSplit[i].find('/');
            if (slashPos == std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }
            std::vector<std::string> indices = utils::splitString(lineSplit[i], '/');
            if (indices.size() != 3) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices[0]);
            int textCoordIndex = std::stoi(indices[1]);
            int normalIndex = std::stoi(indices[1]);
            // Todo: check for neg or overflow
            if (i == 4) {
                auto a = *(finalVertices.rbegin() + 3 - 1);
                auto b = *(finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                finalVertices.push_back(a);
                b.color = faceColor;
                finalVertices.push_back(b);
            }
            auto currentVertex = parsedVertices[vertexIndex - 1];
            currentVertex.textX = textureCoords[textCoordIndex - 1].x;
            currentVertex.textY = textureCoords[textCoordIndex - 1].y;
            currentVertex.normal = normals[normalIndex - 1];
            currentVertex.color = faceColor;
            finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void Model::parseFaceNormal(
        const VertexVector& parsedVertices,
        std::vector<Vec3f>& normals,
        VertexVector& finalVertices,
        const Vec3f& faceColor,
        const std::vector<std::string>& lineSplit,
        const std::string& line) {
    (void) parsedVertices;
    (void) normals;
    (void) finalVertices;
    (void) faceColor;
    (void) lineSplit;
    (void) line;

}

void Model::determineFaceFormat(const std::vector<std::string>& lineSplit) {
    size_t slashPos = lineSplit[1].find('/');
    if (slashPos == std::string::npos) {
        this->faceFormat = VERTEX;
    } else {
        size_t secondSlashPos = lineSplit[1].find('/', slashPos + 1);
        if (secondSlashPos == std::string::npos) {
            this->faceFormat = VERTEX_TEXTURE;
        } else {
            if (secondSlashPos == slashPos + 1) {
                this->faceFormat = VERTEX_NORMAL;
            } else {
                this->faceFormat = VERTEX_TEXTURE_NORMAL;
            }
        }
    }
}

