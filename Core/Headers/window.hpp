#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <iostream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <error.hpp>
#include <shader.hpp>
#include <textrendering.hpp>
#include <engine.hpp>
#include <error.hpp>
#include <mesh.hpp>
#include <camera.hpp>
#include <color.hpp>
#include <input.hpp>
#include <scene.hpp>

#define CURSOR_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_DISABLED GLFW_CURSOR_DISABLED

class Window
{
private:
    GLFWwindow* window;
    glm::vec2 size;
    GLuint program_id;
	Camera* currentCamera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	GLint model_uniform;
	GLint view_uniform;
	GLint projection_uniform;
	GLint render_as_black_uniform;

    void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback);
	void CalcViewMatrix();
	void CalcProjectionMatrix();
	void CalcModelFromMesh(Mesh mesh);
	
	// Callback pra quando a janela for redimensionada
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	// Função auxiliar para gerar as matrizes bizarras do glm
	static glm::mat4 MakeGlmMatrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	)
	{
		return glm::mat4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33
		);
	}

public:
	Window(int width, int height, const char* name);
    bool ShouldClose();
    void PollEvents();
    void ClearWindow(Color color);
	void DrawText(const std::string str, float x, float y, float scale = 1.0f);
	void DrawMesh(Mesh mesh);
	void SetCamera(Camera* camera);
	// Coisas que precisam ser feitas antes de desenhar (limpar a tela e calcular matrizes de view e projection)
	void PreDrawing(Color clearColor);
	float GetScreenRatio();
	void SetCursorType(int type);
	void DrawScene(Scene scene);
};
#endif