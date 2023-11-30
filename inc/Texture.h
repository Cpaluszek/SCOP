#ifndef INC_TEXTURE_H_
#define INC_TEXTURE_H_

#include <string>
#include <stdexcept>
#include "stb_image.h"
#include "glew.h"
#include "glfw3.h"

class Texture {
 public:
     Texture();

     static void initTextureSettings();

     void loadTextureFile(const char* texturePath) const;
     void bind() const;

     GLuint id = 0;
};

#endif  //INC_TEXTURE_H_
