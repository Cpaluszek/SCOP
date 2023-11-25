#include "MtlParser.h"
#include "ObjParser.h"
#include "Vec3f.h"
#include "utils.h"
#include <stdexcept>

MtlParser::~MtlParser() {
    if (this->mtlFile.is_open()) {
        this->mtlFile.close();
    }
}

void MtlParser::parseMtlFile(const std::string& inputFile) {
    this->mtlFile = std::ifstream(inputFile, std::ios::in);
    if (!mtlFile.is_open()) {
        throw std::runtime_error("Could not open mtl file '" + inputFile + "'");
    }

    std::string line;
    while (std::getline(mtlFile, line)) {
        if (line.empty()) continue;

        VecString tokens = utils::splitString(line, ' ');

        if (tokens.size() == 1 || tokens.at(0) == COMMENT_KEYWORD) continue;

        this->parseLine(tokens, line);
    }
}

void MtlParser::parseLine(VecString& tokens, const std::string& line) {
    if (tokens.at(0) == NAME_KEYWORD) {
        this->mat.name = tokens.at(1);
    } else if (tokens.at(0) == AMBIENT_KEYWORD) {
        tokens.erase(tokens.begin());
        this->mat.ambientColor = parseFloatVector(tokens);
    } else if (tokens.at(0) == DIFFUSE_KEYWORD) {
        tokens.erase(tokens.begin());
        this->mat.diffuseColor = parseFloatVector(tokens);
    } else if (tokens.at(0) == SPECULAR_COLOR_KEYWORD) {
        tokens.erase(tokens.begin());
        this->mat.specularColor = parseFloatVector(tokens);
    } else if (tokens.at(0) == SPECULAR_EXPONENT_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect specular exponent format: " + line);
        }
        this->mat.specularExponent = parseFloat(tokens.at(1));
    } else if (tokens.at(0) == DISSOLVE_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect dissolve format: " + line);
        }
        this->mat.dissolve = parseFloat(tokens.at(1));
    } else if (tokens.at(0) == REFRACTION_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect refraction index format: " + line);
        }
        this->mat.refraction = parseFloat(tokens.at(1));
    } else if (tokens.at(0) == ILLUMINATION_MODEL_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect illumination model format: " + line);
        }
        this->mat.illumModel = parseInt(tokens.at(1));
    } else {
        std::cerr << "Parsing material: '" << line << "' is not yet implemented" << std::endl;
    }
}

// Todo: move to another file
Vec3f MtlParser::parseFloatVector(const VecString& tokens) {
    Vec3f result;

    if (tokens.size() != 3) {
        throw std::runtime_error("Incorrect vector format");
    }
    try {
        result = {
            std::stof(tokens.at(0)),
            std::stof(tokens.at(1)),
            std::stof(tokens.at(2))
        };
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid");
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range");
    }

    return result;
}

float MtlParser::parseFloat(const std::string& value) {
    float result;

    try {
        result = std::stof(value);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid");
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range");
    }

    return result;
}

int MtlParser::parseInt(const std::string& value) {
    int result;

    try {
        result = std::stoi(value);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Argument is invalid");
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Argument is out of range");
    }

    return result;
}

