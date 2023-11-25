#include "Material.h"

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << "Name: " << material.name << "\n"
       << "Ambient Color: " << material.ambientColor << "\n"
       << "Diffuse Color: " << material.diffuseColor << "\n"
       << "Specular Color: " << material.specularColor << "\n"
       << "Specular Exponent: " << material.specularExponent << "\n"
       << "Dissolve: " << material.dissolve << "\n"
       << "Refraction: " << material.refraction << "\n"
       << "Illumination Model: " << material.illumModel << std::endl;

    return os;
}

