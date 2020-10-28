#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>

int main()
{
    Engine engine = Engine();

    Window window = Window(800, 600, "test");

	Mesh box;
	box.MakeBox(Vector3(0, 0, 5), Vector3(2, 2, 2));

	Camera camera = Camera();
	window.SetCamera(camera);

    while (!window.ShouldClose())
    {
		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawMesh(box);
		window.DrawText("Texto de teste", 0.5, 0.5);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}