#pragma once

#include <glad/glad.h>
#include <string>

class Texture{
    public:
        GLuint ID;
        Texture(const std::string& filePath, GLenum textureUnit = GL_TEXTURE0);

        ~Texture();

        void Bind() const;
        void Unbind() const;
    private:
        GLenum m_TextureUnit;
};
