#include "Texture.h"

#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const unsigned char* textureSource, int textureSourceSize) {
    glGenTextures(1, &textureID);
    unsigned char* data = stbi_load_from_memory(textureSource, textureSourceSize, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else
        {
            std::cout << "Texture format not supported: " << textureSource << std::endl;
            stbi_image_free(data);
            return;
        }


        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to read from memory: " << textureSource << std::endl;
        stbi_image_free(data);
    }
}
void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

unsigned int Texture::getTexture() const {
    return textureID;
}

unsigned int Texture::getWidth() const {
    return width;
}

unsigned int Texture::getHeight() const {
    return height;
}
