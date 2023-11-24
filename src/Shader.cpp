#include "Shader.h"

void Shader::compileProgram(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (const std::ifstream::failure &e) {
        vShaderFile.close();
        fShaderFile.close();
        throw ;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileError(vertex);
    // Fragment shader
    fragment  = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileError(vertex);

    // Shader Program
    this->id = glCreateProgram();
    if (this->id == 0) {
        throw std::runtime_error("Failed to create shader program");
    }
    try {
        glAttachShader(this->id, vertex);
        glAttachShader(this->id, fragment);
        glLinkProgram(this->id);
        checkProgramError(this->id);
    } catch (const std::exception& e) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        throw;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->id);
}

void Shader::use() const {
    glUseProgram(this->id);
}

void Shader::checkCompileError(const GLuint shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> infoLog(length + 1);
        glGetShaderInfoLog(shader, length, nullptr, infoLog.data());
        throw std::runtime_error(infoLog.data());
    }
}

void Shader::checkProgramError(const GLuint program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        int length;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> infoLog(length + 1);
        glGetShaderInfoLog(program, length, nullptr, infoLog.data());
        throw std::runtime_error(infoLog.data());
    }
}


void Shader::setBool(const std::string &name, const bool value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}


void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(this->id, name.c_str()), x, y);
}


void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z);
}


void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w);
}

void Shader::setMat4(const std::string& name, const Mat4f& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0]);
}

//  void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
//    glUniform2fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
//  }
//  void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
//    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
//  }
//  void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
//    glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
//  }
//  void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
//    glUniformMatrix2fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//  }
//
//  void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
//    glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//  }
//
