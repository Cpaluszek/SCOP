#include "Texture.h"

void Texture::initTextureSettings() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture() {
    glGenTextures(1, &this->id);
    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("Failed to generate texture");
    }
    this->bind();
}

void Texture::loadTextureFile(const char* texturePath) const {
    int width, height, nbChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(texturePath, &width, &height, &nbChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);    
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        throw std::runtime_error("Failed to load texture");
    }

    glActiveTexture(GL_TEXTURE0);
    this->bind();
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("Failed to bind texture");
    }
}

