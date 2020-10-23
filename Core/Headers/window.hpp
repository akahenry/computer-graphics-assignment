#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <iostream>
#include <iostream>
#include <glad/glad.h>   // Cria��o de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Cria��o de janelas do sistema operacional
// Headers da biblioteca GLM: cria��o de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <error.hpp>
#include <shader.hpp>
#include <textrendering.hpp>

#include <engine.hpp>
#include <error.hpp>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class Window
{
private:
    GLFWwindow* window;
    glm::vec2 size;
    float screenRatio;
    GLuint program_id;
    

    void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback = &FramebufferSizeCallback);


public:
	Window(int width, int height, const char* name)
	{
        this->window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (!this->window)
        {
            glfwTerminate();
            ErrorCallback(1, "ERROR: glfwCreateWindow() failed.\n");
            std::exit(EXIT_FAILURE);
        }
        this->size = glm::vec2(width, height);

        // Definimos a fun��o de callback que ser� chamada sempre que o usu�rio
        // pressionar alguma tecla do teclado ...
        //glfwSetKeyCallback(window, KeyCallback);
        // ... ou clicar os bot�es do mouse ...
        //glfwSetMouseButtonCallback(window, MouseButtonCallback);
        // ... ou movimentar o cursor do mouse em cima da janela ...
        //glfwSetCursorPosCallback(window, CursorPosCallback);
        // ... ou rolar a "rodinha" do mouse.
        //glfwSetScrollCallback(window, ScrollCallback);

        SetFrameBufferSizeCallback();

        // Indicamos que as chamadas OpenGL dever�o renderizar nesta janela
        glfwMakeContextCurrent(this->window);

        // Carregamento de todas fun��es definidas por OpenGL 3.3, utilizando a
        // biblioteca GLAD.
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        // Imprimimos no terminal informa��es sobre a GPU do sistema
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* glversion = glGetString(GL_VERSION);
        const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

        printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

        // Carregamos os shaders de v�rtices e de fragmentos que ser�o utilizados
        // para renderiza��o. Veja slides 176-196 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
        //
        // Note que o caminho para os arquivos "shader_vertex.glsl" e
        // "shader_fragment.glsl" est�o fixados, sendo que assumimos a exist�ncia
        // da seguinte estrutura no sistema de arquivos:
        //
        //    + FCG_Lab_0X/
        //    |
        //    +--+ bin/
        //    |  |
        //    |  +--+ Release/  (ou Debug/ ou Linux/)
        //    |     |
        //    |     o-- main.exe
        //    |
        //    +--+ src/
        //       |
        //       o-- shader_vertex.glsl
        //       |
        //       o-- shader_fragment.glsl
        //       |
        //       o-- ...
        //
        GLuint vertex_shader_id = LoadShader_Vertex("shader_vertex.glsl");
        GLuint fragment_shader_id = LoadShader_Fragment("shader_fragment.glsl");

        // Criamos um programa de GPU utilizando os shaders carregados acima
        this->program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

        // Constru�mos a representa��o de um tri�ngulo
        //GLuint vertex_array_object_id = BuildTriangles();

        // Inicializamos o c�digo para renderiza��o de texto.
        TextRendering_Init();

        // Buscamos o endere�o das vari�veis definidas dentro do Vertex Shader.
        // Utilizaremos estas vari�veis para enviar dados para a placa de v�deo
        // (GPU)! Veja arquivo "shader_vertex.glsl".
        GLint model_uniform = glGetUniformLocation(program_id, "model"); // Vari�vel da matriz "model"
        GLint view_uniform = glGetUniformLocation(program_id, "view"); // Vari�vel da matriz "view" em shader_vertex.glsl
        GLint projection_uniform = glGetUniformLocation(program_id, "projection"); // Vari�vel da matriz "projection" em shader_vertex.glsl
        GLint render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black"); // Vari�vel booleana em shader_vertex.glsl

        // Habilitamos o Z-buffer. Veja slides 104-116 do documento Aula_09_Projecoes.pdf.
        glEnable(GL_DEPTH_TEST);

        // Vari�veis auxiliares utilizadas para chamada � fun��o
        // TextRendering_ShowModelViewProjection(), armazenando matrizes 4x4.
        //glm::mat4 the_projection;
        //glm::mat4 the_model;
        //glm::mat4 the_view;
	}

    bool ShouldClose();

    // Verificamos com o sistema operacional se houve alguma intera��o do
    // usu�rio (teclado, mouse, ...). Caso positivo, as fun��es de callback
    // definidas anteriormente usando glfwSet*Callback() ser�o chamadas
    // pela biblioteca GLFW.
    void PollEvents();

    // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor �
    // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto �:
    // Vermelho, Verde, Azul, Alpha (valor de transpar�ncia).
    // Conversaremos sobre sistemas de cores nas aulas de Modelos de Ilumina��o.
    //
    //                      R           G           B           A
    void ClearColor(float red, float green, float blue, float alpha);
};
#endif