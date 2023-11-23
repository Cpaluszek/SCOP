#ifndef INC_TEXTURE_H_
#define INC_TEXTURE_H_

#include <string>
#include <stdexcept>
#include "./stb_image.h"
#include "../lib/GLEW/include/glew.h"
#include "glfw3.h"

// Note: Model should contains a texture instance?
class Texture {
 public:
     Texture();
     void loadTextureFile(const char* texturePath);

     GLuint id;
};

#endif  //INC_TEXTURE_H_
