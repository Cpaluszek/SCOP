#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <vector>
#include <string>

typedef std::vector<std::string> VecString;

namespace utils {
    VecString splitString(const std::string& input, char delimiter);
}

#endif  // INC_UTILS_H_
