#include "ObjParser.h"

ObjParser::ObjParser() {
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

ObjParser::~ObjParser() {
    if (objFile.is_open()) {
        objFile.close();
    }
}

void ObjParser::parseObjFile(const std::string& inputFile) {
    this->objFile = std::ifstream(inputFile, std::ios::in);
    if (!objFile.is_open()) {
        throw std::runtime_error("Could not open input file '" + inputFile + "'");
    }

    this->parentPath = std::filesystem::path(inputFile).parent_path();

    std::string line;
    while (std::getline(objFile, line)) {
        if (line.empty()) continue;

        VecString tokens = utils::splitString(line, ' ');
        if (tokens.size() == 1 || tokens.at(0) == COMMENT_KEYWORD) continue;
        
        this->parseLine(tokens, line);
    }
 
    if (!this->materialFile.empty()) {
        std::cout << "Parsing mtl file is not yet implemented" << std::endl;
        std::cout << "File name: " << this->materialFile << std::endl;

        MtlParser materialParser;
        materialParser.parseMtlFile(materialFile);
        this->material = materialParser.mat;
    }
}

void ObjParser::parseLine(const VecString& tokens, const std::string& line) {
    // Note: maybe use map with functions to iterate
    if (tokens.at(0) == VERTEX_KEYWORD) {
        if (!finalVertices.empty()) {
            throw std::runtime_error("Vertex to need be listed before faces");
        }
        this->parseVertex(tokens, line);
    } else if (tokens.at(0) == FACE_KEYWORD) {
        if (parsedVertices.empty()) {
            throw std::runtime_error("Vertex need be listed before faces");
        } 
        if (tokens.size() < 4 || tokens.size() > 5) {
            throw std::runtime_error("Incorrect face format: should be triangle or quad");
        }
        if (finalVertices.empty()) {
            this->determineFaceFormat(tokens);
        }

        switch (this->faceFormat) {
            case VERTEX:
                this->parseFace(getRandomColor(), tokens, line);
                break;
            case VERTEX_TEXTURE:
                this->parseFaceTexture(getRandomColor(), tokens, line);
                break;
            case VERTEX_TEXTURE_NORMAL:
                this->parseFaceTextureNormal(getRandomColor(), tokens, line);
                break;
            case VERTEX_NORMAL:
                this->parseFaceNormal(getRandomColor(), tokens, line);
                break;
        }
    }
    else if (tokens.at(0) == VERTEX_NORMALS_KEYWORD) {
        this->parseVertexNormal(tokens, line);
    } else if (tokens.at(0) == SMOOTH_SHADING_KEYWORD) {
        this->parseSmoothShading(tokens);
    } else if (tokens.at(0) == TEXT_COORDS_KEYWORD) {
        this->parseVertexTextureCoords(tokens, line);
    } else if (tokens.at(0) == MAT_FILE_KEYWORD) {
        this->checkMaterialFileArgument(tokens);
    } else if (tokens.at(0) == MAT_NAME_KEYWORD) {
        std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
    } else if (tokens.at(0) == OBJ_NAME_KEYWORD) {
        std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
    } else if (tokens.at(0) == GROUP_NAME_KEYWORD) {
        std::cerr << "Parsing: '" << line << "' is not implemented yet" << std::endl;
    } else if (tokens.at(0) == LINE_KEYWORD) {
        std::cerr << "This project does not support line elements" << std::endl;
    } else if (tokens.at(0) == PARAM_SPACE_VERTICES_KEYWORD) {
        std::cerr << "This project does not support parameter space vertices" << std::endl;
    } else {
        std::cerr << "Parsing: '" << line << "' unknown keyword" << std::endl;
    }
}

void ObjParser::parseVertex(const VecString& tokens, const std::string& line) {
    if (tokens.size() < 4 || tokens.size() > 5) {
        throw std::runtime_error("Incorrect vertex format: (x, y, z, [w])");
    }

    try {
        GLfloat x = std::stof(tokens.at(1));
        GLfloat y = std::stof(tokens.at(2));
        GLfloat z = std::stof(tokens.at(3));
        Vertex vertex {
            Vec3f(x, y, z),
            Vec3f(),
            Vec3f(),
            x, y
            
        };
        this->parsedVertices.push_back(vertex);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseVertexNormal(const VecString& tokens, const std::string& line) {
    if (tokens.size() != 4) {
        throw std::runtime_error("Incorrect vertex normal format: (x, y, z)");
    }

    try {
        GLfloat x = std::stof(tokens.at(1));
        GLfloat y = std::stof(tokens.at(2));
        GLfloat z = std::stof(tokens.at(3));
        Vec3f normal(x, y, z);
        this->normals.push_back(Vec3f::normalize(normal));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseVertexTextureCoords(const VecString& tokens, const std::string& line) {
    if (tokens.size() < 2 || tokens.size() > 4) {
        throw std::runtime_error("Incorrect vertex texture coords format: (u, [v, w])");
    }

    try {
        GLfloat u = std::stof(tokens.at(1));
        GLfloat v = tokens.size() > 2 ? std::stof(tokens.at(2)) : 0.0f;
        if (u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f) {
            throw std::runtime_error("Texture coords should in range [0.0f, 1.0f]");
        }
        this->textureCoords.push_back(Vec3f(u, v, 0.0f));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFace(const Vec3f& color, const VecString& tokens, const std::string& line) {
    try {
        for (size_t i = 1; i < tokens.size(); i++) {
            if (i == 4) {
                this->handleQuadToTriangle();
            }

            size_t slashPos = tokens.at(i).find('/');
            if (slashPos != std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }

            int index = std::stoi(tokens.at(i)) - 1;
            if (index < 0) {
                index = this->parsedVertices.size() - index;
            }
            auto currentVertex = this->parsedVertices.at(index);
            currentVertex.color = color;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

// Todo: test
void ObjParser::parseFaceTexture(const Vec3f& color, const VecString& tokens, const std::string& line) {
    try {
        for (size_t i = 1; i < tokens.size(); i++) {
            if (i == 4) {
                this->handleQuadToTriangle();
            }

            size_t slashPos = tokens.at(i).find('/');
            if (slashPos == std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }
            VecString indices = utils::splitString(tokens.at(i), '/');
            if (indices.size() != 2) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices.at(0)) - 1;
            if (vertexIndex < 0) {
                vertexIndex = this->parsedVertices.size() - vertexIndex;
            }
            int textCoordIndex = std::stoi(indices.at(1)) - 1;
            if (textCoordIndex < 0) {
                textCoordIndex = this->textureCoords.size() - textCoordIndex;
            }
            auto currentVertex = this->parsedVertices.at(vertexIndex);
            currentVertex.textX = this->textureCoords.at(textCoordIndex).x;
            currentVertex.textY = this->textureCoords.at(textCoordIndex).y;
            currentVertex.color = color;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFaceTextureNormal(const Vec3f& color, const VecString& tokens,
        const std::string& line) {
    try {
        for (size_t i = 1; i < tokens.size(); i++) {
            if (i == 4) {
                this->handleQuadToTriangle();
            }

            size_t slashPos = tokens.at(i).find('/');
            if (slashPos == std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }
            VecString indices = utils::splitString(tokens.at(i), '/');
            if (indices.size() != 3) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices.at(0)) - 1;
            if (vertexIndex < 0) {
                vertexIndex = this->parsedVertices.size() - vertexIndex;
            }
            int textCoordIndex = std::stoi(indices.at(1)) - 1;
            if (textCoordIndex < 0) {
                textCoordIndex = this->textureCoords.size() - textCoordIndex;
            }
            int normalIndex = std::stoi(indices.at(2)) - 1;
            if (normalIndex < 0) {
                normalIndex = this->normals.size() - normalIndex;
            }
            auto currentVertex = this->parsedVertices.at(vertexIndex);
            currentVertex.textX = this->textureCoords.at(textCoordIndex).x;
            currentVertex.textY = this->textureCoords.at(textCoordIndex).y;
            currentVertex.normal = this->normals.at(normalIndex);
            currentVertex.color = color;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFaceNormal(const Vec3f& color, const VecString& tokens, const std::string& line) {
    try {
        for (size_t i = 1; i < tokens.size(); i++) {
            if (i == 4) {
                this->handleQuadToTriangle();
            }

            size_t slashPos = tokens.at(i).find('/');
            if (slashPos == std::string::npos) {
                throw std::runtime_error("Inconsistent face format");
            }
            VecString indices = utils::splitString(tokens.at(i), '/');
            if (indices.size() != 3 || (indices.size() == 3 && indices.at(1).size() != 0)) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices.at(0)) - 1;
            if (vertexIndex < 0) {
                vertexIndex = this->parsedVertices.size() - vertexIndex;
            }
            int normalIndex = std::stoi(indices.at(2)) - 1;
            if (normalIndex < 0) {
                normalIndex = this->normals.size() - normalIndex;
            }
            auto currentVertex = this->parsedVertices.at(vertexIndex);
            currentVertex.normal = this->normals.at(normalIndex);
            currentVertex.color = color;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::handleQuadToTriangle() {
    auto a = *(this->finalVertices.rbegin() + 3 - 1);
    auto b = *(this->finalVertices.rbegin() + 1 - 1);
    this->finalVertices.push_back(a);
    this->finalVertices.push_back(b);
}

void ObjParser::parseSmoothShading(const VecString& tokens) {
    if (tokens.size() != 2) {
        throw std::runtime_error("Incorrect smooth shading format: (1 / off)");
    }
    if (tokens.at(1) == "1") {
        this->useSmoothShading = true;
    } else if (tokens.at(1) == "off") {
        this->useSmoothShading = false;
    } else {
        throw std::runtime_error("Incorrect smooth shading parameter: " + tokens.at(1));
    }
}

void ObjParser::determineFaceFormat(const VecString& tokens) {
    VecString slashSplit = utils::splitString(tokens.at(1), '/');
    if (slashSplit.size() == 1) {
        this->faceFormat = VERTEX;
    } else if (slashSplit.size() == 2) {
        this->faceFormat = VERTEX_TEXTURE;
    } else if (slashSplit.size() == 3) {
        if (slashSplit.at(1).size() == 0) {
            this->faceFormat = VERTEX_NORMAL;
        } else {
            this->faceFormat = VERTEX_TEXTURE_NORMAL;
        }
    }
}

void ObjParser::checkMaterialFileArgument(const VecString& tokens) {
    if (tokens.size() != 2) {
        std::cerr << "Invalid material file: `mtllib [external .mtl file name]'" << std::endl;
        return;
    }

    std::filesystem::path materialPath(tokens.at(1));
    if (materialPath.extension() != ".mtl") {
        std::cerr << "Invalid material file extension" << std::endl;
        return ;
    }

    std::string materialCompletePath = this->parentPath + "/" + tokens.at(1);
    if (!std::filesystem::exists(materialCompletePath)) {
        std::cerr << "Invalid material file: " << tokens.at(1) << "does not exists" << std::endl;
        return;
    }

    if (!this->materialFile.empty()) {
        std::cerr << "Second material file will be ignored" << std::endl;
        return;
    }

    this->materialFile = materialCompletePath;
}

Vec3f ObjParser::getRandomColor() {
    return Vec3f(this->dis(gen), this->dis(gen), this->dis(gen));
}

