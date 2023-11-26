#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <vector>
#include <string>
#include "Vec3f.h"

typedef std::vector<std::string> VecString;

namespace utils {
    VecString splitString(const std::string& input, char delimiter);
    Vec3f parseFloatVector(const VecString& tokens);
    float parseFloat(const std::string& value);
    int parseInt(const std::string& value);
}

#endif  // INC_UTILS_H_
