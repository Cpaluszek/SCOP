#ifndef INC_MATERIAL_H_
#define INC_MATERIAL_H_

#include "Vec3f.h"

struct Material {
    std::string name;
    Vec3f ambientColor;
    Vec3f diffuseColor;
    Vec3f specularColor;
    float specularExponent;
    float dissolve;
    float refraction;
};

std::ostream& operator<<(std::ostream& os, const Material& material);

#endif  //INC_MATERIAL_H_
