#include "../inc/utils.h"

VecString utils::splitString(const std::string& input, char delimiter) {
    VecString tokens;

    size_t start = 0;
    size_t end;

    while ((end = input.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(input.substr(start));

    return tokens;
}

