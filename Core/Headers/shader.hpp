#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>   // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <engine.hpp>

#include <light.hpp>

class Shader
{
private:
	LightSource illumination;

    /**
	 * Load and compiles the shader
	 * 
     * @param[in] filename a string representing the filename of the shader
     * @param[in] shader_id an integer representing the id of the shader
	 */
    void LoadShader(const char* filename, GLuint shader_id);

    /**
	 * Load and compiles the vertex shader
	 * 
     * @param[in] filename a string representing the filename of the vertex shader
     * 
     * @param[out] vertex_shader_id an integer representing the id of the vertex shader
	 */
    GLuint LoadShader_Vertex(const char* filename);

    /**
	 * Load and compiles the fragment shader
	 * 
     * @param[in] filename a string representing the filename of the fragment shader
     * 
     * @param[out] fragment_shader_id an integer representing the id of the fragment shader
	 */
    GLuint LoadShader_Fragment(const char* filename);

public:
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLuint program_id;

    /**
	 * Compute an instance of Shader class.
	 * 
	 * @param[out] Shader an instance of Shader
	 */
    Shader();

    /**
	 * Compute an instance of Shader class.
	 * 
     * @param[in] vertex_shader_filename a string representing the filename of the vertex shader
     * @param[in] fragment_shader_filename a string representing the filename of the fragment shader
     * 
	 * @param[out] Shader an instance of Shader
	 */
    Shader(const char* vertex_shader_filename, const char* fragment_shader_filename);

    /**
	 * Set the illumination for the shader (deprecated)
	 * 
     * @param[in] illumination a LightSource with the illumination to be used in this shader
	 */
    void SetIllumination(LightSource illumination);
};

#endif