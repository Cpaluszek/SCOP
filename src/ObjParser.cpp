#include "../inc/ObjParser.h"
#include <random>

// Todo: in face parsing test for invalid index access

ObjParser::ObjParser() {
    // Setup random distribution for colors
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

// [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
void ObjParser::parseObjFile(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        // Todo: How to process invalid or unsupported keyword - exit??
        if (line.empty()) continue ;

        VecString lineSplit = utils::splitString(line, ' ');
        if (lineSplit.size() == 1 || lineSplit[0] == COMMENT_KEYWORD) continue ;
        
        this->parseLine(lineSplit, line);
    }
}

void ObjParser::parseLine(const VecString& lineSplit, const std::string& line) {
    // Note: maybe use map with functions to iterate
    if (lineSplit[0] == VERTEX_KEYWORD) {
        if (finalVertices.size() != 0) {
            throw std::runtime_error("Vertex to need be listed before faces");
        }
        this->parseVertex(lineSplit, line);
    } else if (lineSplit[0] == FACE_KEYWORD) {
        if (parsedVertices.size() == 0) {
            throw std::runtime_error("Vertex need be listed before faces");
        } 
        if (lineSplit.size() < 4 || lineSplit.size() > 5) {
            throw std::runtime_error("Incorrect face format: should be triangle or quad");
        }
        if (finalVertices.size() == 0) {
            this->determineFaceFormat(lineSplit);
        }

        switch (this->faceFormat) {
            case VERTEX:
                this->parseFace(getRandomColor(), lineSplit, line);
                break;
            case VERTEX_TEXTURE:
                this->parseFaceTexture(getRandomColor(), lineSplit, line);
                break;
            case VERTEX_TEXTURE_NORMAL:
                this->parseFaceTextureNormal(getRandomColor(), lineSplit, line);
                break;
            case VERTEX_NORMAL:
                this->parseFaceNormal(getRandomColor(), lineSplit, line);
                break;
        }
    }
    else if (lineSplit[0] == VERTEX_NORMALS_KEYWORD) {
        this->parseVertexNormal(lineSplit, line);
    } else if (lineSplit[0] == SMOOTH_SHADING_KEYWORD) {
        this->parseSmoothShading(lineSplit);
    } else if (lineSplit[0] == TEXT_COORDS_KEYWORD) {
        this->parseVertexTextureCoords(lineSplit, line);
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

void ObjParser::parseVertex(
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
        this->parsedVertices.push_back(vertex);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range:" + line);
    }
}

void ObjParser::parseVertexNormal(
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
        this->normals.push_back(Vec3f::normalize(normal));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseVertexTextureCoords(
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
        this->textureCoords.push_back(Vec3f(u, v, 0.0f));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFace(
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
                auto a = *(this->finalVertices.rbegin() + 3 - 1);
                auto b = *(this->finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                this->finalVertices.push_back(a);
                b.color = faceColor;
                this->finalVertices.push_back(b);
            }
            auto currentVertex = this->parsedVertices[index - 1];
            currentVertex.color = faceColor;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

// Todo: test
void ObjParser::parseFaceTexture(
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
                auto a = *(this->finalVertices.rbegin() + 3 - 1);
                auto b = *(this->finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                this->finalVertices.push_back(a);
                b.color = faceColor;
                this->finalVertices.push_back(b);
            }
            auto currentVertex = this->parsedVertices[vertexIndex - 1];
            currentVertex.textX = this->textureCoords[textCoordIndex - 1].x;
            currentVertex.textY = this->textureCoords[textCoordIndex - 1].y;
            currentVertex.color = faceColor;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFaceTextureNormal(
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
            int normalIndex = std::stoi(indices[2]);
            // Todo: check for neg or overflow
            if (i == 4) {
                auto a = *(finalVertices.rbegin() + 3 - 1);
                auto b = *(finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                finalVertices.push_back(a);
                b.color = faceColor;
                finalVertices.push_back(b);
            }
            auto currentVertex = this->parsedVertices[vertexIndex - 1];
            currentVertex.textX = this->textureCoords[textCoordIndex - 1].x;
            currentVertex.textY = this->textureCoords[textCoordIndex - 1].y;
            currentVertex.normal = this->normals[normalIndex - 1];
            currentVertex.color = faceColor;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseFaceNormal(
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
            if (indices.size() != 3 || (indices.size() == 3 && indices[1].size() != 0)) {
                throw std::runtime_error("Inconsistent face format");
            }

            int vertexIndex = std::stoi(indices[0]);
            int normalIndex = std::stoi(indices[2]);
            // Todo: check for neg or overflow
            if (i == 4) {
                auto a = *(this->finalVertices.rbegin() + 3 - 1);
                auto b = *(this->finalVertices.rbegin() + 1 - 1);
                a.color = faceColor;
                this->finalVertices.push_back(a);
                b.color = faceColor;
                this->finalVertices.push_back(b);
            }
            auto currentVertex = this->parsedVertices[vertexIndex - 1];
            currentVertex.normal = this->normals[normalIndex - 1];
            currentVertex.color = faceColor;
            this->finalVertices.push_back(currentVertex);
        }
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range: " + line);
    }
}

void ObjParser::parseSmoothShading(const VecString& lineSplit) {
    if (lineSplit.size() != 2) {
        throw std::runtime_error("Incorrect smooth shading format: (1 / off)");
    }
    if (lineSplit[1] == "1") {
        this->useSmoothShading = true;
    } else if (lineSplit[1] == "off") {
        this->useSmoothShading = false;
    } else {
        throw std::runtime_error("Incorrect smooth shading parameter: " + lineSplit[1]);
    }
}

void ObjParser::determineFaceFormat(const std::vector<std::string>& lineSplit) {
    VecString slashSplit = utils::splitString(lineSplit[1], '/');
    if (slashSplit.size() == 1) {
        this->faceFormat = VERTEX;
    } else if (slashSplit.size() == 2) {
        this->faceFormat = VERTEX_TEXTURE;
    } else if (slashSplit.size() == 3) {
        if (slashSplit[1].size() == 0) {
            this->faceFormat = VERTEX_NORMAL;
        } else {
            this->faceFormat = VERTEX_TEXTURE_NORMAL;
        }
    }
}

Vec3f ObjParser::getRandomColor() {
    return Vec3f(this->dis(gen), this->dis(gen), this->dis(gen));
}

