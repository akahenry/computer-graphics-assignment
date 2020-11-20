#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <glad/glad.h>

class Engine
{
    public:
        /**
         * Compute an instance of Engine class.
         * 
         * @param[out] Engine an instance of Engine
         */
        Engine();

        /**
         * Creates the GPU program returning its id
         * 
         * @param[in] vertex_shader_id the id of a vertex shader
         * @param[in] fragment_shader_id the id of a fragment shader
         * 
         * @param[out] gpu_program_id the id of the GPU program
         */
		static GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

        /**
         * Terminates all the operations gracefully
         */
        void Terminate();
};

#endif