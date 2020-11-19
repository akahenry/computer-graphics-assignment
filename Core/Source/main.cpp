#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>
#include <ctime>


int main()
{
	clock_t tStart = clock();
	Engine engine = Engine();

	Window window = Window(800, 600, "The Labyrinth");

	ReflectanceComponents defaultReflectance;
	defaultReflectance.diffuse = Vector3(0.08, 0.4, 0.8);
	defaultReflectance.specular = Vector3(0.8, 0.8, 0.8);
	defaultReflectance.ambient = defaultReflectance.diffuse/2;

	/*Mesh boxMesh;
	boxMesh.MakeBox({ 0, 0, -5 }, { 2, 2, 2 });
	boxMesh.rotationAxis = {0, 1.0, 0};
	GraphicObject box(&boxMesh, defaultReflectance, 32);

	Mesh groundMesh;
	groundMesh.MakeBox({ 0, -3, -5 }, { 10, 1, 10 });
	GraphicObject ground(&groundMesh, defaultReflectance, 1);*/

	Mesh bunnyMesh;
	bunnyMesh.LoadFromObj("bunny.obj");
	GraphicObject bunny({ 0,0,-5 }, &bunnyMesh, defaultReflectance, 100);

	Mesh penguinMesh;
	penguinMesh.LoadFromObj("PenguinBaseMesh.obj");
	GraphicObject penguin({ 5,0,-5 }, &penguinMesh, defaultReflectance, 100);
	penguin.SetTexture("Penguin Diffuse Color.png");
	GraphicObject penguin2({ 10,0,-5 }, &penguinMesh, defaultReflectance, 100);

	Texture worldTexture = Texture("world.png");
	penguin2.SetTexture(worldTexture);
	bunny.SetTexture(worldTexture);

	FreeCamera camera = FreeCamera({ 0,0,0 },-0.1f,-2000.f);
	window.SetCamera(&camera);

	LightSource light = LightSource({ 5, 0, -5 }, { 1, 1, 1 }, {0.2, 0.2, 0.2}, LightType::Phong);
	LightSource gouraudLight = LightSource({ 5, 0, -5 }, { 1, 1, 1 }, { 0.2, 0.2, 0.2 }, LightType::Gouraud);

	Scene scene1;
	scene1.AddLight(&light);
	scene1.AddObject(&bunny);
	scene1.AddObject(&penguin);
	scene1.AddObject(&penguin2);

	Scene scene2;
	scene2.AddLight(&gouraudLight);
	scene2.AddObject(&bunny);
	scene2.AddObject(&penguin);
	scene2.AddObject(&penguin2);
	/*scene1.AddObject(&box);
	scene1.AddObject(&ground);*/

	float t = 0;
	bool buttonPressed = false;
	bool buttonPressedLastFrame = false; // talvez seja interessante passar essa funcionalidade pra classe input
	bool mouseEscondido = false;

    while (!window.ShouldClose())
    {
		t += 0.001;
		bunny.rotationAngle = t;
		bunny.position.y = sin(t);

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