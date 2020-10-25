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

class Window
{
private:
    GLFWwindow* window;
    glm::vec2 size;
    float screenRatio;
    GLuint program_id;

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback);

public:
	Window(int width, int height, const char* name);

    bool ShouldClose();

    // Verificamos com o sistema operacional se houve alguma intera��o do
    // usu�rio (teclado, mouse, ...). Caso positivo, as fun��es de callback
    // definidas anteriormente usando glfwSet*Callback() ser�o chamadas
    // pela biblioteca GLFW.
    void PollEvents();

    // Limpa a tela com a cor escolhida
    void ClearWindow(float red, float green, float blue, float alpha);

	void DrawText(const std::string str, float x, float y, float scale = 1.0f);
};
#endif