#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <glad/glad.h>

class Engine
{
    public:
        Engine();
		static GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
        void Terminate();
};

#endif