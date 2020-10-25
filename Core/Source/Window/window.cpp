#include <window.hpp>

float g_ScreenRatio;

Window::Window(int width, int height, const char* name)
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
	// redimensionar a tela ...
	SetFrameBufferSizeCallback(&FramebufferSizeCallback);
	// ... ou pressionar alguma tecla do teclado ...
	//glfwSetKeyCallback(window, KeyCallback);
	// ... ou clicar os bot�es do mouse ...
	//glfwSetMouseButtonCallback(window, MouseButtonCallback);
	// ... ou movimentar o cursor do mouse em cima da janela ...
	//glfwSetCursorPosCallback(window, CursorPosCallback);
	// ... ou rolar a "rodinha" do mouse.
	//glfwSetScrollCallback(window, ScrollCallback);

	// Indicamos que as chamadas OpenGL dever�o renderizar nesta janela
	glfwMakeContextCurrent(this->window);

	// Carregamento de todas fun��es definidas por OpenGL 3.3, utilizando a
	// biblioteca GLAD.
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLuint vertex_shader_id = LoadShader_Vertex("shader_vertex.glsl");
	GLuint fragment_shader_id = LoadShader_Fragment("shader_fragment.glsl");

	// Criamos um programa de GPU utilizando os shaders carregados acima
	this->program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

	// Constru�mos a representa��o de um tri�ngulo
	//GLuint vertex_array_object_id = BuildTriangles();

	// Inicializamos o c�digo para renderiza��o de texto.
	TextRendering_Init();

	// Buscamos o endere�o das vari�veis definidas dentro do Vertex Shader.
	GLint model_uniform = glGetUniformLocation(program_id, "model");
	GLint view_uniform = glGetUniformLocation(program_id, "view");
	GLint projection_uniform = glGetUniformLocation(program_id, "projection");
	GLint render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black");

	// Habilitamos o Z-buffer
	glEnable(GL_DEPTH_TEST);
	// Habilitamos o Backface Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Vari�veis auxiliares utilizadas para chamada � fun��o
	// TextRendering_ShowModelViewProjection(), armazenando matrizes 4x4.
	//glm::mat4 the_projection;
	//glm::mat4 the_model;
	//glm::mat4 the_view;
}

// Callback pra quando a janela for redimensionada
void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Atualiza o Viewport Mapping
    glViewport(0, 0, width, height);

	// esse ratio � usado pra definir a matriz de proje��o, pra n�o ter distor��es indesejadas
    g_ScreenRatio = (float)width / height;
}

void Window::SetFrameBufferSizeCallback(GLFWframebuffersizefun callback)
{
    int width = int(size.x);
    int height = int(size.y);

    glfwSetFramebufferSizeCallback(this->window, callback);
	// For�amos a chamada do callback acima, para definir g_ScreenRatio
    glfwSetWindowSize(this->window, width, height);

    this->screenRatio = g_ScreenRatio;
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Window::PollEvents()
{
    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo
    // os shaders de v�rtice e fragmentos).
    glUseProgram(this->program_id);

    // Mostra o buffer que tem a tela desenhada no �ltimo frame (necess�rio fazer esse swap pra n�o ter screen tearing)
    glfwSwapBuffers(this->window);

    glfwPollEvents();
}

void Window::ClearWindow(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);

    // limpa framebuffer com a cor escolhida e reseta os pixels do z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::DrawText(const std::string str, float x, float y, float scale)
{
	TextRendering_PrintString(this->window, str, x, y, scale);
}