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
	box.MakeBox(Vector3(1, 1, 5), Vector3(2, 2, 2));
	box.rotationAxis = Vector3(1.0, 1.0, 1.0);

	Camera camera = Camera();
	window.SetCamera(camera);

	float t = 0;

    while (!window.ShouldClose())
    {
		t += 0.001;
		box.rotationAngle = t;

		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawMesh(box);
		window.DrawText("Texto de teste", 0.5, 0.5);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}