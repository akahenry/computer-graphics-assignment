#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>

int main()
{
    Engine engine;

    engine.Initialize();

    Window window = Window(800, 600, "test");

	Mesh box;
	box.MakeBox(Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));

    while (!window.ShouldClose())
    {
		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawMesh(box);
		window.DrawText("Texto de teste", 0.5, 0.5);
        window.PollEvents();
    }

    // Fim do programa
    return 0;
}