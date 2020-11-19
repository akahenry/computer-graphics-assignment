#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <tiny_obj_loader/tiny_obj_loader.h>
#include <tiny_obj_loader/stb_image.h>



class Texture
{
public:
    int texture_unit;
    GLuint texture_id;
    GLuint sampler_id;
    unsigned char* data;
    int width;
    int height;

    Texture();
    Texture(const char* filename);
private:
    void LoadTextureImage(const char* filename);
};