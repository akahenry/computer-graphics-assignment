#include <window.hpp>

float g_ScreenRatio;

// Defini��o da fun��o que ser� chamada sempre que a janela do sistema
// operacional for redimensionada, por consequ�ncia alterando o tamanho do
// "framebuffer" (regi�o de mem�ria onde s�o armazenados os pixels da imagem).
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Indicamos que queremos renderizar em toda regi�o do framebuffer. A
    // fun��o "glViewport" define o mapeamento das "normalized device
    // coordinates" (NDC) para "pixel coordinates".  Essa � a opera��o de
    // "Screen Mapping" ou "Viewport Mapping" vista em aula ({+ViewportMapping2+}).
    glViewport(0, 0, width, height);

    // Atualizamos tamb�m a raz�o que define a propor��o da janela (largura /
    // altura), a qual ser� utilizada na defini��o das matrizes de proje��o,
    // tal que n�o ocorra distor��es durante o processo de "Screen Mapping"
    // acima, quando NDC � mapeado para coordenadas de pixels. Veja slides 205-215 do documento Aula_09_Projecoes.pdf.
    //
    // O cast para float � necess�rio pois n�meros inteiros s�o arredondados ao
    // serem divididos!
    g_ScreenRatio = (float)width / height;
}

void Window::SetFrameBufferSizeCallback(GLFWframebuffersizefun callback)
{
    int width = int(size.x);
    int height = int(size.y);

    // Definimos a fun��o de callback que ser� chamada sempre que a janela for
    // redimensionada, por consequ�ncia alterando o tamanho do "framebuffer"
    // (regi�o de mem�ria onde s�o armazenados os pixels da imagem).
    glfwSetFramebufferSizeCallback(this->window, callback);
    glfwSetWindowSize(this->window, width, height); // For�amos a chamada do callback acima, para definir g_ScreenRatio.

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

    // O framebuffer onde OpenGL executa as opera��es de renderiza��o n�o
    // � o mesmo que est� sendo mostrado para o usu�rio, caso contr�rio
    // seria poss�vel ver artefatos conhecidos como "screen tearing". A
    // chamada abaixo faz a troca dos buffers, mostrando para o usu�rio
    // tudo que foi renderizado pelas fun��es acima.
    // Veja o link: Veja o link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics
    glfwSwapBuffers(this->window);

    glfwPollEvents();


}

void Window::ClearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);

    // "Pintamos" todos os pixels do framebuffer com a cor definida acima,
    // e tamb�m resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
