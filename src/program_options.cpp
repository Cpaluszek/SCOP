#include "../inc/program_options.h"

#include <filesystem>
#include <stdexcept>
#include <vector>

namespace {
    std::string   objFile;
}

void program_options::parse(const int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);

    for (const auto& arg : args) {
        if (!std::filesystem::exists(arg)) {
            throw std::runtime_error(arg + ": No such file or directory");
        }
        // Todo: check for .obj extension
        if (!objFile.empty()) {
            throw std::runtime_error("Cannot use multiple .obj files");
        }
        objFile = arg;
    }
}

const std::string& program_options::inputFile() {
    return objFile;
}

