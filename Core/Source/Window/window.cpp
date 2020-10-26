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

	// Definimos a função de callback que será chamada sempre que o usuário
	// redimensionar a tela ...
	SetFrameBufferSizeCallback(&FramebufferSizeCallback);
	// ... ou pressionar alguma tecla do teclado ...
	//glfwSetKeyCallback(window, KeyCallback);
	// ... ou clicar os botões do mouse ...
	//glfwSetMouseButtonCallback(window, MouseButtonCallback);
	// ... ou movimentar o cursor do mouse em cima da janela ...
	//glfwSetCursorPosCallback(window, CursorPosCallback);
	// ... ou rolar a "rodinha" do mouse.
	//glfwSetScrollCallback(window, ScrollCallback);

	// Indicamos que as chamadas OpenGL deverão renderizar nesta janela
	glfwMakeContextCurrent(this->window);

	// Carregamento de todas funções definidas por OpenGL 3.3, utilizando a
	// biblioteca GLAD.
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLuint vertex_shader_id = LoadShader_Vertex("shader_vertex.glsl");
	GLuint fragment_shader_id = LoadShader_Fragment("shader_fragment.glsl");

	// Criamos um programa de GPU utilizando os shaders carregados acima
	this->program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

	// Inicializamos o código para renderização de texto.
	TextRendering_Init();

	// Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
	model_uniform = glGetUniformLocation(program_id, "model");
	view_uniform = glGetUniformLocation(program_id, "view");
	projection_uniform = glGetUniformLocation(program_id, "projection");
	render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black");

	// Habilitamos o Z-buffer
	glEnable(GL_DEPTH_TEST);
	// Habilitamos o Backface Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

// Callback pra quando a janela for redimensionada
void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Atualiza o Viewport Mapping
    glViewport(0, 0, width, height);

	// esse ratio é usado pra definir a matriz de projeção, pra não ter distorções indesejadas
    g_ScreenRatio = (float)width / height;
}

void Window::SetFrameBufferSizeCallback(GLFWframebuffersizefun callback)
{
    int width = int(size.x);
    int height = int(size.y);

    glfwSetFramebufferSizeCallback(this->window, callback);
	// Forçamos a chamada do callback acima, para definir g_ScreenRatio
    glfwSetWindowSize(this->window, width, height);

    this->screenRatio = g_ScreenRatio;
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Window::PollEvents()
{
    // Mostra o buffer que tem a tela desenhada no último frame (necessário fazer esse swap pra não ter screen tearing)
    glfwSwapBuffers(this->window);

    glfwPollEvents();
}

void Window::ClearWindow(Color color)
{
    glClearColor(color.R, color.G, color.B, color.A);

    // limpa framebuffer com a cor escolhida e reseta os pixels do z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4 Window::CalcViewMatrix()
{
	Vector3 u = currentCamera.getRelativeRightVector();
	Vector3 v = currentCamera.getRelativeUpVector();
	Vector3 w = currentCamera.getRelativeBackVector();

	return Window::MakeGlmMatrix(
		u.x , u.y , u.z , (-u).DotProduct(currentCamera.position),
		v.x , v.y , v.z , (-v).DotProduct(currentCamera.position),
		w.x , w.y , w.z , (-w).DotProduct(currentCamera.position),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

glm::mat4 Window::CalcProjectionMatrix()
{
	float n = currentCamera.nearPlane;
	float f = currentCamera.farPlane;
	float fov = currentCamera.fov;

	float t = fabs(currentCamera.nearPlane) * tanf(this->currentCamera.fov / 2.0f);
	float b = -t;
	float r = t * screenRatio;
	float l = -r;

	glm::mat4 M = MakeGlmMatrix(
		2/(r-l), 0.0f	, 0.0f	 , -(r+l)/(r-l),
        0.0f   , 2/(t-b), 0.0f	 , -(t+b)/(t-b),
        0.0f   , 0.0f	, 2/(f-n), -(f+n)/(f-n),
        0.0f   , 0.0f	, 0.0f	 , 1.0f
	);

	glm::mat4 P = MakeGlmMatrix(
		n	, 0.0f, 0.0f, 0.0f,
		0.0f, n	  , 0.0f, 0.0f,
		0.0f, 0.0f, n+f , -f*n,
		0.0f, 0.0f, 1.0f, 0.0f
	);

	return -M * P;
}

glm::mat4 Window::CalcModelFromMesh(Mesh mesh)
{
	glm::mat4 S = MakeGlmMatrix(
		mesh.scale.x, 0.0f		  , 0.0f		, 0.0f,
		0.0f		, mesh.scale.y, 0.0f		, 0.0f,
		0.0f		, 0.0f		  , mesh.scale.z, 0.0f,
		0.0f		, 0.0f		  , 0.0f		, 1.0f
	);


	float c = cos(mesh.rotationAngle);
	float s = sin(mesh.rotationAngle);

	Vector3 v = mesh.rotationAxis.Normalized();

	float vx = v.x;
	float vy = v.y;
	float vz = v.z;

	// rotação em torno de um eixo arbitrário
	glm::mat4 R = MakeGlmMatrix(
		vx*vx*(1-c)+c	, vx*vy*(1-c)-vz*s, vx*vz*(1-c)+vy*s, 0.0f,
        vx*vy*(1-c)+vz*s, vy*vy*(1-c)+c	  , vy*vz*(1-c)-vx*s, 0.0f,
        vx*vz*(1-c)-vy*s, vy*vz*(1-c)+vx*s, vz*vz*(1-c)+c	, 0.0f,
        0.0f			, 0.0f			  , 0.0f			, 1.0f
	);

	glm::mat4 T = MakeGlmMatrix(
		1.0f, 0.0f, 0.0f, mesh.position.x,
		0.0f, 1.0f, 0.0f, mesh.position.y,
		0.0f, 0.0f, 1.0f, mesh.position.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return T * R * S;
}

void Window::PreDrawing(Color clearColor)
{
	this->ClearWindow(clearColor);
	this->viewMatrix = this->CalcViewMatrix();
	this->projectionMatrix = this->CalcProjectionMatrix();

	glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Window::DrawText(const std::string str, float x, float y, float scale)
{
	TextRendering_PrintString(this->window, str, x, y, scale);
}

void Window::DrawMesh(Mesh mesh)
{
	// Pedimos para a GPU utilizar o programa de GPU criado no construtor
	glUseProgram(this->program_id);
	glBindVertexArray(mesh.vaoId);
	
	glm::mat4 modelMatrix = CalcModelFromMesh(mesh);

	glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform1i(render_as_black_uniform, false);
	glDrawElements(
		mesh.renderingMode,
		mesh.numIndices,
		GL_UNSIGNED_INT,
		(void*)0
	);
}

void Window::SetCamera(Camera camera)
{
	this->currentCamera = camera;
}