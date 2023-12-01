#ifndef INC_MTLPARSER_H_
#define INC_MTLPARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Material.h"
#include "Vec3f.h"
#include "utils.h"

#define COMMENT_KEYWORD "#"
#define NAME_KEYWORD "newmtl"
#define AMBIENT_KEYWORD "Ka"
#define DIFFUSE_KEYWORD "Kd"
#define SPECULAR_COLOR_KEYWORD "Ks"
#define SPECULAR_EXPONENT_KEYWORD "Ns"
#define DISSOLVE_KEYWORD "d"
#define REFRACTION_KEYWORD "Ni"

#define INVERT_DISSOLVE_KEYWORD "Tr"

class MtlParser {
 public:
     ~MtlParser();

     void parseMtlFile(const std::string& inputFile);

    Material mat;

 private:
    std::ifstream mtlFile;

    void parseLine(VecString& tokens, const std::string& line);
};

#endif  //INC_MTLPARSER_H_
