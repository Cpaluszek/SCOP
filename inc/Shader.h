#ifndef INC_SHADER_H_
#define INC_SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../lib/GLEW/include/glew.h"
#include "./math.h"

class Shader {
 public:
     GLuint id;

     Shader() = default;
     ~Shader();

     void compileProgram(const char* vertexPath, const char* fragmentPath);

     void use() const;

     // Utility
     void setBool(const std::string &name, bool value) const;
     void setInt(const std::string &name, int value) const;
     void setFloat(const std::string &name, float value) const;
     //    void setVec2(const std::string &name, const glm::vec2 &value) const;
     void setVec2(const std::string &name, float x, float y) const;
     //    void setVec3(const std::string &name, const glm::vec3 &value) const;
     void setVec3(const std::string &name, float x, float y, float z) const;
     //    void setVec4(const std::string &name, const glm::vec4 &value) const;
     void setVec4(const std::string &name, float x, float y, float z, float w) const;
     //    void setMat2(const std::string &name, const glm::mat2 &mat) const;
     //    void setMat3(const std::string &name, const glm::mat3 &mat) const;
     void setMat4(const std::string& name, const Mat4f &mat) const;

 private:
     static void checkCompileError(const GLuint shader);
     static void checkProgramError(const GLuint program);
};

#endif  // INC_SHADER_H_
