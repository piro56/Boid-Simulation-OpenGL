#pragma once
#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"
#include <string>
class Texture {
private:
    unsigned int ID;
    bool loaded;
    GLenum textureSlot;
public:
    // 
    Texture(GLenum glTexture);

    ~Texture();
    inline unsigned int get_ID() {
        return this->ID;
    };

    // Parameters
    void setParameteri(GLenum pName, int param);
    void setParameterfv(GLenum pName, const float* params);
    // load png and JPG texture
    // only load ONCE.
    void load();        // generic load -> based off of extension ending...
    void loadPNG(std::string filePath, bool flip);
    void loadJPG(std::string filePath, bool flip);
    // MANUAL LOADING
    void load_image(std::string filePath, bool flip);
    void tex_image_2D();

    // Enabling and setting active.
    void setActive();
    void bindEnable();

};