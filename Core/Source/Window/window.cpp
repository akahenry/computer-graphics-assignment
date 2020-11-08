#include <window.hpp>

Window::Window(int width, int height, const char* name, Shader shader)
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
	glfwSetKeyCallback(window, &Input::Keyboard::KeyboardButtonCallback);
	// ... ou clicar os bot�es do mouse ...
	glfwSetMouseButtonCallback(window, &Input::Mouse::MouseButtonCallback);
	// ... ou movimentar o cursor do mouse em cima da janela ...
	glfwSetCursorPosCallback(window, &Input::Mouse::CursorPosCallback);
	// ... ou rolar a "rodinha" do mouse.
	//glfwSetScrollCallback(window, ScrollCallback);

	// Indicamos que as chamadas OpenGL dever�o renderizar nesta janela
	glfwMakeContextCurrent(this->window);

	// Carregamento de todas fun��es definidas por OpenGL 3.3, utilizando a
	// biblioteca GLAD.
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	this->shader = shader;

	GLuint vertex_shader_id = this->shader.vertex_shader_id;
	GLuint fragment_shader_id = this->shader.fragment_shader_id;

	// Criamos um programa de GPU utilizando os shaders carregados acima
	this->program_id = this->shader.program_id;

	// Inicializamos o c�digo para renderiza��o de texto.
	TextRendering_Init();

	// Buscamos o endere�o das vari�veis definidas dentro do Vertex Shader.
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

float Window::GetScreenRatio()
{
	int width;
	int height;
	glfwGetWindowSize(this->window, &width, &height);
	return (float)width / height;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Atualiza o Viewport Mapping
    glViewport(0, 0, width, height);
}

void Window::SetFrameBufferSizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(this->window, callback);
	// For�amos a chamada do callback acima, para definir g_ScreenRatio
    glfwSetWindowSize(this->window, size.x, size.y);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Window::PollEvents()
{
    // Mostra o buffer que tem a tela desenhada no �ltimo frame (necess�rio fazer esse swap pra n�o ter screen tearing)
    glfwSwapBuffers(this->window);
    glfwPollEvents();
	Input::PollInputEvents();
}

void Window::ClearWindow(Color color)
{
    glClearColor(color.R, color.G, color.B, color.A);

    // limpa framebuffer com a cor escolhida e reseta os pixels do z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::CalcViewMatrix()
{
	Vector3 u = currentCamera->getRelativeRightVector();
	Vector3 v = currentCamera->getRelativeUpVector();
	Vector3 w = currentCamera->getRelativeBackVector();

	this->viewMatrix = Window::MakeGlmMatrix(
		u.x , u.y , u.z , -u.DotProduct(currentCamera->position),
		v.x , v.y , v.z , -v.DotProduct(currentCamera->position),
		w.x , w.y , w.z , -w.DotProduct(currentCamera->position),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Window::CalcProjectionMatrix()
{
	float n = currentCamera->nearPlane;
	float f = currentCamera->farPlane;
	float fov = currentCamera->fov;

	float t = fabs(n) * tanf(fov / 2.0f);
	float b = -t;
	float r = t * GetScreenRatio();
	float l = -r;

	glm::mat4 M = MakeGlmMatrix(
		2.0f/(r-l), 0.0f	  , 0.0f	  , -(r+l)/(r-l),
        0.0f	  , 2.0f/(t-b), 0.0f	  , -(t+b)/(t-b),
        0.0f	  , 0.0f	  , 2.0f/(f-n), -(f+n)/(f-n),
        0.0f	  , 0.0f	  , 0.0f	  , 1.0f
	);

	glm::mat4 P = MakeGlmMatrix(
		n	, 0.0f, 0.0f, 0.0f,
		0.0f, n	  , 0.0f, 0.0f,
		0.0f, 0.0f, n+f , -f*n,
		0.0f, 0.0f, 1.0f, 0.0f
	);

	this->projectionMatrix = -M * P;
}

void Window::CalcModelFromMesh(Mesh mesh)
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

	// rota��o em torno de um eixo arbitr�rio
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

	this->modelMatrix = T * R * S;
}

void Window::PreDrawing(Color clearColor)
{
	// Pedimos para a GPU utilizar o programa de GPU criado no construtor
	glUseProgram(this->program_id);

	this->ClearWindow(clearColor);
	this->CalcViewMatrix();
	this->CalcProjectionMatrix();

	glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(this->viewMatrix));
	glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
}

void Window::DrawText(const std::string str, float x, float y, float scale)
{
	TextRendering_PrintString(this->window, str, x, y, scale);
}

void Window::DrawMesh(Mesh mesh)
{
	glBindVertexArray(mesh.vaoId);
	
	CalcModelFromMesh(mesh);

	glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform1i(render_as_black_uniform, false);
	glDrawElements(
		mesh.renderingMode,
		mesh.numIndices,
		GL_UNSIGNED_INT,
		0
	);
	glBindVertexArray(0);
}

void Window::SetCamera(Camera* camera)
{
	this->currentCamera = camera;
}

void Window::SetCursorType(int type)
{
	glfwSetInputMode(window, GLFW_CURSOR, type);
}

void Window::DrawObject(GraphicObject object)
{
	this->DrawMesh(*(object.mesh));
}

void Window::DrawScene(Scene scene)
{
	for (GraphicObject object : scene.objectList)
	{
		this->DrawObject(object);
	}
}