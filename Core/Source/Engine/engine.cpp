#include <iostream>
#include <glad/glad.h>   // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional
// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>

#include <error.hpp>
#include <shader.hpp>
#include <textrendering.hpp>

#include <engine.hpp>


Engine::Engine()
{
    // Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
    // sistema operacional, onde poderemos renderizar com OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos o callback para impressão de erros da GLFW no terminal
    glfwSetErrorCallback(ErrorCallback);

    // Pedimos para utilizar OpenGL versão 3.3 (ou superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Pedimos para utilizar o perfil "core", isto é, utilizaremos somente as
    // funções modernas de OpenGL.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
};

// Esta função cria um programa de GPU, o qual contém obrigatoriamente um
// Vertex Shader e um Fragment Shader.
GLuint Engine::CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
	// Criamos um identificador (ID) para este programa de GPU
	GLuint program_id = glCreateProgram();

	// Definição dos dois shaders GLSL que devem ser executados pelo programa
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	// Linkagem dos shaders acima ao programa
	glLinkProgram(program_id);

	// Verificamos se ocorreu algum erro durante a linkagem
	GLint linked_ok = GL_FALSE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

	// Imprime no terminal qualquer erro de linkagem
	if (linked_ok == GL_FALSE)
	{
		GLint log_length = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

		// Alocamos memória para guardar o log de compilação.
		// A chamada "new" em C++ é equivalente ao "malloc()" do C.
		GLchar* log = new GLchar[log_length];

		glGetProgramInfoLog(program_id, log_length, &log_length, log);

		std::string output;

		output += "ERROR: OpenGL linking of program failed.\n";
		output += "== Start of link log\n";
		output += log;
		output += "\n== End of link log\n";

		// A chamada "delete" em C++ é equivalente ao "free()" do C
		delete[] log;

		fprintf(stderr, "%s", output.c_str());
	}

	// Retornamos o ID gerado acima
	return program_id;
}

void Engine::Terminate()
{
    // Finalizamos o uso dos recursos do sistema operacional
    glfwTerminate();
}