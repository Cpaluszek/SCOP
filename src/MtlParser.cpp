#include "MtlParser.h"
#include "ObjParser.h"
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

void MtlParser::parseLine(const VecString& tokens, const std::string& line) {
    (void) tokens;
    std::cout << line << std::endl;
}
