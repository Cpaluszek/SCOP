#include "utils.h"

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

Vec3f utils::parseFloatVector(const VecString& tokens) {
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

float utils::parseFloat(const std::string& value) {
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

int utils::parseInt(const std::string& value) {
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


