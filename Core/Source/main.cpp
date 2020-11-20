#include "GLFW/linmath.h"
#include <engine.hpp>
#include <window.hpp>
#include <mesh.hpp>
#include <color.hpp>
#include <utils.hpp>


int main()
{
	Engine engine = Engine();

	Window window = Window(800, 600, "The Labyrinth");
	window.SetFrameRateLimit(100);
	
	FreeCamera freeCamera = FreeCamera({ 0,5,-10 }, -0.1f, -2000.f);
	LookAtCamera lookAtCamera = LookAtCamera({ 0,0,0 }, Vector3(10, 10, -10), -0.1f, -100.0f);
	bool isLookAt = true;
	window.SetCamera(&lookAtCamera);

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
	GraphicObject car({ 0,0,0 }, &carMesh, defaultReflectance, 100);
	car.SetTexture("textures/Crysler_new_yorker_Color.png");
	car.scale = Vector3(0.005, 0.005, 0.005);
	car.origin = Vector3(0, 0, 1);
	car.rotationAxis = {0,1,0};
	car.rotationAngle = PI / 2;

	Mesh flagMesh;
	flagMesh.LoadFromObj("Models/flag.obj", "Models/");
	GraphicObject flag({ 0, 0, 2 }, &flagMesh, defaultReflectance, 100);
	flag.SetTexture("Textures/flag.jpg");
	flag.scale = Vector3(0.05, 0.05, 0.05);

	LightSource light = LightSource({ 0, -10, 0 }, { 1, 1, 1 }, {0.2, 0.2, 0.2}, LightType::Phong);

	Scene scene1;
	scene1.AddLight(&light);
	scene1.AddObject(&road);
	scene1.AddObject(&car);
	scene1.AddObject(&flag);

	float animationT = 0; // a animação de transição de primeira pra terceira pessoa usa um t de 0 a 1
	bool cameraIsBeingAnimated = false;
	Vector3 cameraAnimationDestPosition;

	bool buttonPressed = false;
	float t = 0;
	bool buttonPressedLastFrame = false; // talvez seja interessante passar essa funcionalidade pra classe input
	bool hiddenMouse = false;
	float relativeLookAtHorizontalRotation = 0;

    while (!window.ShouldClose())
    {
		buttonPressed = Input::IsButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

		if (buttonPressed && !buttonPressedLastFrame)
		{
			if (hiddenMouse)
			{
				window.SetCursorType(CURSOR_NORMAL);
				hiddenMouse = false;
			}
			else
			{
				window.SetCursorType(CURSOR_DISABLED);
				hiddenMouse = true;
			}
		}

		t += 0.01;

		Vector3 motion = Vector3(0,0,0);
		float carHorizontalRotation = 0;
		float speed = 0.05;


		if (Input::IsButtonPressed(GLFW_KEY_F))
		{
			isLookAt = false;
			cameraIsBeingAnimated = true;

			window.SetCamera(&freeCamera);

			freeCamera.position = lookAtCamera.position;
			freeCamera.setViewVector(lookAtCamera.getViewVector());

			cameraAnimationDestPosition = {
				car.position.x + 0.7f * sin(car.rotationAngle + 0.05f),
				car.position.y + 0.75f,
				car.position.z - 0.7f * cos(car.rotationAngle + 0.05f)
			};
		}
		if (Input::IsButtonPressed(GLFW_KEY_L))
		{
			isLookAt = true;
			cameraIsBeingAnimated = false;
			animationT = 0;
			window.SetCamera(&lookAtCamera);
		}

		if (isLookAt)
		{
			lookAtCamera.pointToLookAt = car.position;

			if (Input::IsButtonPressed(GLFW_KEY_W))
			{
				motion.z = -sin(car.rotationAngle) * speed;
				motion.x = cos(car.rotationAngle) * speed;
			}
			if (Input::IsButtonPressed(GLFW_KEY_A))
			{
				carHorizontalRotation = PI / 2;
			}
			if (Input::IsButtonPressed(GLFW_KEY_S))
			{
				motion.z = sin(car.rotationAngle) * speed;
				motion.x = -cos(car.rotationAngle) * speed;
			}
			if (Input::IsButtonPressed(GLFW_KEY_D))
			{
				carHorizontalRotation = -PI / 2;
			}

			car.position += motion;
			car.rotationAngle += carHorizontalRotation * window.GetDeltaTime();

			if (hiddenMouse)
			{
				relativeLookAtHorizontalRotation += -Input::Mouse::mousePositionDelta.x * 0.001;
			}

			lookAtCamera.position = {
				car.position.x - 5 * cos(car.rotationAngle + relativeLookAtHorizontalRotation),
				car.position.y + 5,
				car.position.z + 5 * sin(car.rotationAngle + relativeLookAtHorizontalRotation)
			};
		}
		// Free Camera
		else
		{
			// Está na transição de teceira e primeira pessoa
			if (cameraIsBeingAnimated)
			{
				float animationSpeed = 0.01;
				animationT += animationSpeed;

				if (animationT > 0.49)
				{
					cameraIsBeingAnimated = false;
				}

				std::cout << animationT << std::endl;

				Vector3 p1 = freeCamera.position;
				Vector3 p4 = cameraAnimationDestPosition;
				Vector3 p2 = (p4 - p1).ProjectedOnto(lookAtCamera.getViewVector()) * 1/3 + p1;
				Vector3 p3 = (p4 - p1).ProjectedOnto(lookAtCamera.getViewVector()) * 2/3 + (p4 - p1).RejectedOnto(lookAtCamera.getViewVector()) + p1;
				freeCamera.position = MovementUtility::Bezier(std::vector<Vector3>{ p1, p2, p3, p4}, animationT);
				//freeCamera.setViewVector(freeCamera.position - MovementUtility::Bezier(std::vector<Vector3>{ p1, p2, p3, p4}, animationT-animationSpeed));
			}
			else
			{
				if (hiddenMouse)
				{
					freeCamera.MoveCameraAngle(-Input::Mouse::mousePositionDelta * 0.001);
				}

				if (Input::IsButtonPressed(GLFW_KEY_W))
				{
					motion.z = speed;
				}
				if (Input::IsButtonPressed(GLFW_KEY_A))
				{
					motion.x = -speed;
				}
				if (Input::IsButtonPressed(GLFW_KEY_S))
				{
					motion.z = -speed;
				}
				if (Input::IsButtonPressed(GLFW_KEY_D))
				{
					motion.x = speed;
				}
				freeCamera.MoveCameraRelatively(motion);
			}
		}
		
		flag.position = MovementUtility::Bezier(std::vector<Vector3>{ { 0, 0, 0 }, { 10,10,0 }, { -10,10,0 }, { 0,0,0 }}, t/10);

		buttonPressedLastFrame = buttonPressed;

		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawScene(scene1);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}