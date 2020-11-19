#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>
#include <ctime>


int main()
{
	Engine engine = Engine();

	Window window = Window(800, 600, "The Labyrinth");

	ReflectanceComponents defaultReflectance;
	defaultReflectance.diffuse = Vector3(0.08, 0.4, 0.8);
	defaultReflectance.specular = Vector3(0.8, 0.8, 0.8);
	defaultReflectance.ambient = defaultReflectance.specular/2;

	/*Mesh boxMesh;
	boxMesh.MakeBox({ 0, 0, -5 }, { 2, 2, 2 });
	boxMesh.rotationAxis = {0, 1.0, 0};
	GraphicObject box(&boxMesh, defaultReflectance, 32);

	Mesh groundMesh;
	groundMesh.MakeBox({ 0, -3, -5 }, { 10, 1, 10 });
	GraphicObject ground(&groundMesh, defaultReflectance, 1);*/

	Mesh roadMesh;
	roadMesh.LoadFromObj("Models/road.obj");
	GraphicObject road({ 0,0,-5 }, &roadMesh, defaultReflectance, 100);
	road.SetTexture("textures/road-texture.jpg");

	Mesh carMesh;
	carMesh.LoadFromObj("Models/Crysler_new_yorker_1980.obj");
	GraphicObject player1({ 0,0,0 }, &carMesh, defaultReflectance, 100);
	player1.SetTexture("textures/Crysler_new_yorker_Color.png");
	player1.scale = Vector3(0.005, 0.005, 0.005);

	FreeCamera freeCamera = FreeCamera({ 0,0,0 },-0.1f,-2000.f);
	LookAtCamera lookAtCamera = LookAtCamera(player1.position, Vector3(10, 10, -10), -0.1f, -100.0f);
	Camera* camera = &lookAtCamera;
	bool isLookAt = true;
	window.SetCamera(camera);

	LightSource light = LightSource({ 0, -10, 0 }, { 1, 1, 1 }, {0.2, 0.2, 0.2}, LightType::Phong);

	Scene scene1;
	scene1.AddLight(&light);
	scene1.AddObject(&road);
	scene1.AddObject(&player1);

	float t = 0;
	bool buttonPressed = false;
	bool buttonPressedLastFrame = false; // talvez seja interessante passar essa funcionalidade pra classe input
	bool mouseEscondido = false;

    while (!window.ShouldClose())
    {
		window.SetCamera(camera);
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
		if (Input::IsButtonPressed(GLFW_KEY_F))
		{
			isLookAt = false;
			camera = &freeCamera;
		}
		if (Input::IsButtonPressed(GLFW_KEY_L))
		{
			isLookAt = true;
			camera = &lookAtCamera;
		}
		// camera.MoveCameraRelatively(motion);

		player1.position += motion;

		if (isLookAt)
			lookAtCamera.pointToLookAt = player1.position;
		else
			freeCamera.MoveCameraAngle(-Input::Mouse::mousePositionDelta * 0.001);
		
		std::cout << freeCamera.horizontalAngle;

		buttonPressedLastFrame = buttonPressed;

		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawScene(scene1);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}