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
        this->mesh->position.x += velocity;
    } else if (direction == RIGHT) {
        this->mesh->position.x -= velocity;
    } else if (direction == FORWARD) {
        this->mesh->position.z -= velocity;
    } else if (direction == BACKWARD) {
        this->mesh->position.z += velocity;
    }
}

// [Wavefront .obj file - Wikipedia](https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=OBJ%20(or%20.,OBJ%20geometry%20format)
void Model::loadOBJFile(std::ifstream& file) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    VertexVector parsedVertices;
    VertexVector finalVertices;

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
            this->parseVertex(parsedVertices, lineSplit, line);
        } else if (lineSplit[0] == FACE_KEYWORD) {
            Vec3f randomColor(dis(gen), dis(gen), dis(gen));
            this->parseFace(parsedVertices, finalVertices, randomColor, lineSplit, line);
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

void Model::parseVertex(VertexVector& parsedVertices,
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
            x, y
            
        };
        parsedVertices.push_back(vertex);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid: " + line);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range:" + line);
    }
}

void Model::parseFace(
             const VertexVector& parsedVertices,
             VertexVector& finalVertices,
             const Vec3f& faceColor,
             const std::vector<std::string>& lineSplit,
             const std::string& line) {

    if (parsedVertices.size() == 0) {
        throw std::runtime_error("Incorrect file format: need vertices to specify faces");
    }
    if (lineSplit.size() < 4 || lineSplit.size() > 5) {
        throw std::runtime_error("Incorrect face format: should be triangle or quad");
    }
    try {
        for (size_t i = 1; i < lineSplit.size(); i++) {
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

