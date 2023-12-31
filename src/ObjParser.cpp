#include "ObjParser.h"
#include "Vertex.h"

ObjParser::ObjParser() {
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->dis = std::uniform_int_distribution<int>(0, palette.size() - 1);
}

ObjParser::~ObjParser() {
    if (objFile.is_open()) objFile.close();
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
       
        try {
            this->parseLine(tokens);
        } catch (const std::exception& e) {
            std::cerr << "'" << line << "'" << std::endl;
            for (auto t: tokens) {
                std::cerr << "-" << t << "-" << std::endl;
            }
            throw;
        }
    }

    this->computeFaces();
 
    if (!this->materialFile.empty()) {
        std::cout << "Material file name: " << this->materialFile << std::endl;

        MtlParser materialParser;
        materialParser.parseMtlFile(materialFile);
        this->material = materialParser.mat;
    }
}

void ObjParser::parseLine(VecString& tokens) {
    if (tokens.at(0) == VERTEX_KEYWORD) {
        this->parseVertex(tokens);
    } else if (tokens.at(0) == FACE_KEYWORD) {
        this->parseFace(tokens);
    }
    else if (tokens.at(0) == VERTEX_NORMALS_KEYWORD) {
        this->parseVertexNormal(tokens);
    } else if (tokens.at(0) == TEXT_COORDS_KEYWORD) {
        this->parseVertexTextureCoords(tokens);
    } else if (tokens.at(0) == MAT_FILE_KEYWORD) {
        this->checkMaterialFileArgument(tokens);
    }
}

void ObjParser::parseVertex(VecString& tokens) {
    if (tokens.size() < 4 || tokens.size() > 5) {
        throw std::runtime_error("Incorrect vertex format: (x, y, z, [w])");
    }

    tokens.erase(tokens.begin());
    Vec3f pos = utils::parseFloatVector(tokens);
    Vertex vertex {
        pos,
        Vec3f(),
        Vec3f(),
        pos.x, pos.y
    };
    this->parsedVertices.push_back(vertex);
}

void ObjParser::parseVertexNormal(VecString& tokens) {
    if (tokens.size() != 4) {
        throw std::runtime_error("Incorrect vertex normal format: (x, y, z)");
    }

    tokens.erase(tokens.begin());
    Vec3f normal = utils::parseFloatVector(tokens);
    this->normals.push_back(Vec3f::normalize(normal));
}

void ObjParser::parseVertexTextureCoords(VecString& tokens) {
    if (tokens.size() < 2 || tokens.size() > 4) {
        throw std::runtime_error("Incorrect vertex texture coords format: (u, [v, w])");
    }

    GLfloat u = utils::parseFloat(tokens.at(1));
    GLfloat v = tokens.size() > 2 ? utils::parseFloat(tokens.at(2)) : 0.0f;
    this->textureCoords.push_back(Vec3f(u, v, 0.0f));
}

void ObjParser::parseFace(const VecString& tokens) {
    std::vector<int> currentFace;
    std::vector<int> currentFaceTexture;
    std::vector<int> currentFaceNormal;

    if (tokens.size() < 4 || tokens.size() > 5) {
        throw std::runtime_error("Incorrect face format: should be triangle or quad");
    }
    if (this->faces.empty()) {
        this->determineFaceFormat(tokens);
    }

    for (size_t i = 1; i < tokens.size(); i++) {
        if (this->vertexFormat == VERTEX && tokens.at(i).find('/') != std::string::npos) {
            throw std::runtime_error("Inconsistent face format");
        }
        VecString indices = utils::splitString(tokens.at(i), '/');

        int vertexIndex = utils::parseInt(indices.at(0)) - 1;
        if (vertexIndex < 0) {
            vertexIndex = this->parsedVertices.size() - vertexIndex;
        }
        currentFace.push_back(vertexIndex);

        if (this->vertexFormat == VERTEX_TEXTURE_NORMAL || this->vertexFormat == VERTEX_TEXTURE) {
            if (indices.size() < 2 || indices.size() > 3) {
                throw std::runtime_error("Inconsistent face format");
            }
            int textCoordIndex = utils::parseInt(indices.at(1)) - 1;
            if (textCoordIndex < 0) {
                textCoordIndex = this->textureCoords.size() - textCoordIndex;
            }
            currentFaceTexture.push_back(textCoordIndex);
        }

        if (this->vertexFormat == VERTEX_TEXTURE_NORMAL || this->vertexFormat == VERTEX_NORMAL) {
            if (indices.size() != 3) {
                throw std::runtime_error("Inconsistent face format");
            }
            int normalIndex = utils::parseInt(indices.at(2)) - 1;
            if (normalIndex < 0) {
                normalIndex = this->normals.size() - normalIndex;
            }
            currentFaceNormal.push_back(normalIndex);
        }
    }
    this->faces.push_back(currentFace);
    if (this->vertexFormat == VERTEX_TEXTURE_NORMAL || this->vertexFormat == VERTEX_TEXTURE) {
        this->textureIndices.push_back(currentFaceTexture);
    }
    if (this->vertexFormat == VERTEX_TEXTURE_NORMAL || this->vertexFormat == VERTEX_NORMAL) {
        this->normalIndices.push_back(currentFaceNormal);
    }
}

void ObjParser::determineFaceFormat(const VecString& tokens) {
    VecString slashSplit = utils::splitString(tokens.at(1), '/');
    if (slashSplit.size() == 1) {
        this->vertexFormat = VERTEX;
    } else if (slashSplit.size() == 2) {
        this->vertexFormat = VERTEX_TEXTURE;
    } else if (slashSplit.size() == 3) {
        if (slashSplit.at(1).size() == 0) {
            this->vertexFormat = VERTEX_NORMAL;
        } else {
            this->vertexFormat = VERTEX_TEXTURE_NORMAL;
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
    return palette.at(this->dis(gen));
}


void ObjParser::computeFaces() {
    if (this->faces.empty()) {
        throw std::runtime_error("Missing faces in .obj file");
    }
    if (this->parsedVertices.empty()) {
        throw std::runtime_error("Missing vertices in .obj file");
    }

    size_t index = 0;
    for (auto face: this->faces) {
        Vec3f faceColor = this->getRandomColor();
        for (size_t i = 0; i < face.size(); i++) {
            if (i == 3) {
                handleQuadToTriangle();
            }
            Vertex current = this->parsedVertices.at(face[i]);
            if (this->vertexFormat == VERTEX_TEXTURE || this->vertexFormat == VERTEX_TEXTURE_NORMAL) {
                Vec3f textureCoordinate = this->textureCoords.at(this->textureIndices.at(index).at(i));
                current.textX = textureCoordinate.x;
                current.textY = textureCoordinate.y;
            }
            if (this->vertexFormat == VERTEX_NORMAL || this->vertexFormat == VERTEX_TEXTURE_NORMAL) {
                Vec3f normal = this->normals.at(this->normalIndices.at(index).at(i));
                current.normal = normal;
            }

            current.color = faceColor;
            this->finalVertices.push_back(current);
        }
        index++;
    }
}

void ObjParser::handleQuadToTriangle() {
    auto a = *(this->finalVertices.rbegin() + 3 - 1);
    auto b = *(this->finalVertices.rbegin() + 1 - 1);
    this->finalVertices.push_back(a);
    this->finalVertices.push_back(b);
}

// void ObjParser::parseSmoothShading(const VecString& tokens) {
//     if (tokens.size() != 2) {
//         throw std::runtime_error("Incorrect smooth shading format: (1 / off)");
//     }
//     if (tokens.at(1) == "1") {
//         this->useSmoothShading = true;
//     } else if (tokens.at(1) == "off" || tokens.at(1) == "0") {
//         this->useSmoothShading = false;
//     } else {
//         throw std::runtime_error("Incorrect smooth shading parameter: " + tokens.at(1));
//     }
// }

