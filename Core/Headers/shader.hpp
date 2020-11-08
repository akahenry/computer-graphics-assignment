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

    void LoadShader(const char* filename, GLuint shader_id);
    GLuint LoadShader_Vertex(const char* filename);
    GLuint LoadShader_Fragment(const char* filename);
    void RefreshIllumination();

public:
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLuint program_id;

    Shader();
    Shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
    void SetIllumination(LightSource illumination);
};

#endif