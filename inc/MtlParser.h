#ifndef INC_MTLPARSER_H_
#define INC_MTLPARSER_H_

#include <fstream>
#include <string>
#include "Vec3f.h"
#include "utils.h"

#define COMMENT_KEYWORD "#"
#define NAME_KEYWORD "newmtl"
#define AMBIENT_KEYWORD "Ka"
#define DIFFUSE_KEYWORD "Kd"
#define SPECULAR_COLOR_KEYWORD "Ks"
#define SPECULAR_EXPONENT_KEYWORD "Ns"
#define DISSOLVE_KEYWORD "d"
#define REFRACTION_INDEX "Ni"

#define TRANSMISSION_FILTER "Tf"    // Note: implement?
#define INVERT_DISSOLVE_KEYWORD "Tr"

#define ILLUMINATION_MODEL_KEYWORD "illum"
/*
 * 0. Color on and Ambient off
 * 1. Color on and Ambient on
 * 2. Highlight on
 * 3. Reflection on and Ray trace on
 * 4. Transparency: Glass on, Reflection: Ray trace on
 * 5. Reflection: Fresnel on and Ray trace on
 * 6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
 * 7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
 * 8. Reflection on and Ray trace off
 * 9. Transparency: Glass on, Reflection: Ray trace off
 * 10. Casts shadows onto invisible surfaces
*/

struct Material {
    std::string name;
    Vec3f ambientColor;
    Vec3f diffuseColor;
    Vec3f specularColor;
    float specularExponent;
    float dissolve;
    int illumModel;     // Note: switch to enum?
};

class MtlParser {
 public:
     ~MtlParser();

     void parseMtlFile(const std::string& inputFile);

 private:
    // Note: manage multiple materials?
    Material mat;

    std::ifstream mtlFile;

    void parseLine(const VecString& tokens, const std::string& line);
};

#endif  //INC_MTLPARSER_H_
