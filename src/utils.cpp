#include "../inc/utils.h"

std::vector<std::string> utils::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end = 0;

    while ((end = input.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(input.substr(start));

    return tokens;
}

