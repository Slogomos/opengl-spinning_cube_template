#include "textures.h"
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(const std::string& filePath, GLenum textureUnit) 
  : ID(0), m_TextureUnit(textureUnit){
    stbi_set_flip_vertically_on_load(true);

    int imgWidth, imgHeight, nrChannels;
    unsigned char *bytes = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);

    if (!bytes) {
      std::cout << "Failed to load texture image" << std::endl;
      return;
    }
    else std::cout << "Loaded texture: '" << filePath << "' (" << imgWidth << ", " << imgHeight << ")" << std::endl;

    glGenTextures(1, &ID);
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);

    GLenum format = GL_RGB;
    if (nrChannels == 4) format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

Texture::~Texture(){
  glDeleteTextures(1, &ID);
}

void Texture::Bind() const {
  glActiveTexture(m_TextureUnit);
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}