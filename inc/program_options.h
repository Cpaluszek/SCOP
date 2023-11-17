#ifndef INC_PROGRAM_OPTIONS_H_
#define INC_PROGRAM_OPTIONS_H_

#define DESIRED_EXTENSION ".obj"

#include <string>


namespace program_options {
    void parse(int argc, char* argv[]);

    const std::string& inputFile();
};

#endif  // INC_PROGRAM_OPTIONS_H_
