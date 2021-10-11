#include "Texture.h"

Texture::Texture(GLenum glTexture) {
    this->textureSlot = glTexture;
    glGenTextures(1, &this->ID);
}

void Texture::bindEnable() {
    glActiveTexture(this->textureSlot);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::setActive() {
    glActiveTexture(this->textureSlot);
}

void Texture::setParameteri(GLenum pName, int param) {
    glTexParameteri(GL_TEXTURE_2D, pName, param );
}

void Texture::setParameterfv(GLenum pName, const float* params) {
    glTexParameterfv(GL_TEXTURE_2D, pName, params);
}
void Texture::loadJPG(std::string filePath, bool flip) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(filePath.c_str(),
                          &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, 
        height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << filePath << "\n";
    }
    stbi_image_free(data);
}

void Texture::loadPNG(std::string filePath, bool flip) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(filePath.c_str(),
                          &width, &height, &nrChannels, 4);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, 
        height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << filePath << "\n";
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    
}