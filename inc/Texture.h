#ifndef INC_TEXTURE_H_
#define INC_TEXTURE_H_

#include <string>
#include <stdexcept>
#include "./stb_image.h"
#include "../lib/GLEW/include/glew.h"
#include "glfw3.h"

class Texture {
 public:
     Texture();
     void loadTextureFile(const char* texturePath);

 private:
     GLuint id;
};

#endif  //INC_TEXTURE_H_
