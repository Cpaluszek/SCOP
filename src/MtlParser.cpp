#include "MtlParser.h"

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
        this->mat.ambientColor = utils::parseFloatVector(tokens);
    } else if (tokens.at(0) == DIFFUSE_KEYWORD) {
        tokens.erase(tokens.begin());
        this->mat.diffuseColor = utils::parseFloatVector(tokens);
    } else if (tokens.at(0) == SPECULAR_COLOR_KEYWORD) {
        tokens.erase(tokens.begin());
        this->mat.specularColor = utils::parseFloatVector(tokens);
    } else if (tokens.at(0) == SPECULAR_EXPONENT_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect specular exponent format: " + line);
        }
        this->mat.specularExponent = utils::parseFloat(tokens.at(1));
    } else if (tokens.at(0) == DISSOLVE_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect dissolve format: " + line);
        }
        this->mat.dissolve = utils::parseFloat(tokens.at(1));
    } else if (tokens.at(0) == REFRACTION_KEYWORD) {
        if (tokens.size() != 2) {
            throw std::runtime_error("Incorrect refraction index format: " + line);
        }
        this->mat.refraction = utils::parseFloat(tokens.at(1));
    } 
}

