#ifndef INC_PROGRAM_OPTIONS_H_
#define INC_PROGRAM_OPTIONS_H_

#include <string>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include "./utils.h"

namespace program_options {
    void parse(int argc, char* argv[]);

    const std::string& inputFile();
}

#endif  // INC_PROGRAM_OPTIONS_H_
