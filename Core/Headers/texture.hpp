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

    /**
	 * Compute an instance of Texture class with default values
     * 
	 * @param[out] Texture an instance of Texture
	 */
    Texture();

    /**
	 * Compute an instance of Texture class from a texture file
     * 
     * @param[in] filename a string representing the name of the texture file
     * 
	 * @param[out] Texture an instance of Texture
	 */
    Texture(const char* filename);
private:
    /**
	 * Loads the texture file, filling all the class attributes 
     * 
     * @param[in] filename a string representing the name of the texture file
	 */
    void LoadTextureImage(const char* filename);
};