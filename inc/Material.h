#ifndef INC_MATERIAL_H_
#define INC_MATERIAL_H_

#include "Vec3f.h"

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
    // Todo: check range 0-1000
    float specularExponent;
    float dissolve;
    // Todo: Td: tranmission color filter?
    float refraction;
    // Todo: remove
    int illumModel;
};

std::ostream& operator<<(std::ostream& os, const Material& material);

#endif  //INC_MATERIAL_H_
