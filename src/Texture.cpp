#include "Texture.h"

Texture::Texture(GLenum glTexture) {
    this->textureSlot = glTexture;
    glGenTextures(1, &this->ID);
}

void Texture::bindEnable() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glActiveTexture(this->textureSlot);
}

void Texture::setActive() {
    glActiveTexture(this->textureSlot);
}

void Texture::setParameteri(GLenum pName, int param) {
    glTexParameteri(GL_TEXTURE_2D, pName, param);
}

void setParameterfv(GLenume pName, const float* params) {
    glTexParameterfv(GL_TEXTURE_2D, pName, params);
}

void loadPNG(std::string filePath, bool flip) {
    int width, height, nrChannels;
    if(flip) {
        stbi_set_flip_vertically_on_load(true);
    } else {
        stbi_set_flip_vertically_on_load(false);
    }

    unsigned char *data = stbi_load(filePath.c_str(),
                          &width, &height, &nrChannels, 4);
    if(data) {
        glTexImage(GL_TEXTURE_2D, 0, GL_RGBA2, width, 
        height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << filePath << "\n";
    }
    stbi_image_free(data);
}
