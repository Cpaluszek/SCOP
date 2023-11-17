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
        std::filesystem::path path(arg);
        if (path.extension() != DESIRED_EXTENSION) {
            throw std::runtime_error("File is not in the correct format");
        }
        if (!objFile.empty()) {
            throw std::runtime_error("Cannot use multiple .obj files");
        }
        objFile = arg;
    }
}

const std::string& program_options::inputFile() {
    return objFile;
}

