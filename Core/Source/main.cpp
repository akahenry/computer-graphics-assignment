#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>

int main()
{
	Engine engine = Engine();

	Window window = Window(800, 600, "The Labyrinth");

	Mesh box;
	box.MakeBox({ 0, 0, -5 }, { 2, 2, 2 });
	box.rotationAxis = {0, 1.0, 0};

	Mesh ground;
	ground.MakeBox({ 0, -3, -5 }, { 10, 1, 10 });

	FreeCamera camera = FreeCamera({ 0,0,0 },-0.1f,-2000.f);
	window.SetCamera(&camera);

	Scene scene1;
	scene1.AddMesh(&box);
	scene1.AddMesh(&ground);

	float t = 0;
	bool buttonPressed = false;
	bool buttonPressedLastFrame = false; // talvez seja interessante passar essa funcionalidade pra classe input
	bool mouseEscondido = false;

    while (!window.ShouldClose())
    {
		t += 0.001;
		box.rotationAngle = t;
		box.position.y = sin(t);

		buttonPressed = Input::IsButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

		if (buttonPressed && !buttonPressedLastFrame)
		{
			if (mouseEscondido)
			{
				window.SetCursorType(CURSOR_NORMAL);
				mouseEscondido = false;
			}
			else
			{
				window.SetCursorType(CURSOR_DISABLED);
				mouseEscondido = true;
			}
		}

		Vector3 motion = Vector3(0,0,0);
		if (Input::IsButtonPressed(GLFW_KEY_W))
		{
			motion.z = 0.01;
		}
		if (Input::IsButtonPressed(GLFW_KEY_A))
		{
			motion.x = -0.01;
		}
		if (Input::IsButtonPressed(GLFW_KEY_S))
		{
			motion.z = -0.01;
		}
		if (Input::IsButtonPressed(GLFW_KEY_D))
		{
			motion.x = 0.01;
		}
		camera.MoveCameraRelatively(motion);

		if (mouseEscondido)
			camera.MoveCameraAngle(-Input::Mouse::mousePositionDelta * 0.001);

		buttonPressedLastFrame = buttonPressed;

		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawScene(scene1);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}