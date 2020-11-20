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

	int score = 0;
	auto begin_lap = glfwGetTime();

	Mesh roadMesh;
	roadMesh.LoadFromObj("Models/road.obj");
	GraphicObject road({ 0,0,-5 }, &roadMesh, defaultReflectance, 100);
	road.SetTexture("textures/road-texture.jpg");

	Mesh carMesh;
	carMesh.LoadFromObj("Models/Crysler_new_yorker_1980.obj");
	GraphicObject car({ 4,0,-2 }, &carMesh, defaultReflectance, 100);
	car.SetTexture("textures/Crysler_new_yorker_Color.png");
	car.scale = Vector3(0.005, 0.005, 0.005);
	car.origin = Vector3(0, 0, 1);
	car.rotationAxis = {0,1,0};

	Mesh cowMesh;
	cowMesh.LoadFromObj("Models/cow.obj");
	GraphicObject cow1({ 0,0,0 }, &cowMesh, defaultReflectance, 100);
	cow1.rotationAxis = { 0,1,0 };
	GraphicObject cow2({ 5,0,0 }, &cowMesh, defaultReflectance, 100);
	cow2.rotationAxis = { 0,1,0 };

	Mesh flagMesh;
	flagMesh.LoadFromObj("Models/flag.obj", "Models/");
	GraphicObject flag(MovementUtility::FlagPosition(road, score), &flagMesh, defaultReflectance, 100);
	flag.SetTexture("Textures/flag.jpg");
	flag.scale = Vector3(0.05, 0.05, 0.05);

	LightSource light = LightSource({ 0, -10, 0 }, { 1, 1, 1 }, {0.2, 0.2, 0.2}, LightType::Phong);

	Scene scene1;
	scene1.AddLight(&light);
	scene1.AddObject(&road);
	scene1.AddObject(&car);
	scene1.AddObject(&flag);
	scene1.AddObject(&cow1);
	scene1.AddObject(&cow2);

	float animationT = 0; // a animação de transição de primeira pra terceira pessoa usa um t de 0 a 1
	bool cameraIsBeingAnimated = false;
	Vector3 cameraAnimationDestPosition;

	bool buttonPressed = false;
	float t = 0;
	bool buttonPressedLastFrame = false; // talvez seja interessante passar essa funcionalidade pra classe input
	bool hiddenMouse = false;
	float relativeLookAtHorizontalRotation = 0;
	float carSpeed = 0.05;
	float speed = 5;

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


		if (Input::IsButtonPressed(GLFW_KEY_F))
		{
			isLookAt = false;
			cameraIsBeingAnimated = true;

			window.SetCamera(&freeCamera);

			freeCamera.position = lookAtCamera.position;
			freeCamera.setViewVector(lookAtCamera.getViewVector());

			cameraAnimationDestPosition = {
				car.position.x - 0.7f * sin(car.rotationAngle + 0.05f),
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

		if (Input::IsButtonPressed(GLFW_KEY_G))
		{
			light.lightType = LightType::Gouraud;
		}
		if (Input::IsButtonPressed(GLFW_KEY_P))
		{
			light.lightType = LightType::Phong;
		}

		if (isLookAt)
		{
			lookAtCamera.pointToLookAt = car.position;

			if (Input::IsButtonPressed(GLFW_KEY_W))
			{
				carSpeed += 0.01;
			}
			else if (Input::IsButtonPressed(GLFW_KEY_S))
			{
				carSpeed = std::max(carSpeed - 0.005, -1.0);
			}
			else
			{
				carSpeed = std::max(carSpeed - 0.005, 0.0);
			}

			if (Input::IsButtonPressed(GLFW_KEY_A))
			{
				carHorizontalRotation = PI / 2;
			}
			
			if (Input::IsButtonPressed(GLFW_KEY_D))
			{
				carHorizontalRotation = -PI / 2;
			}
			

			motion.z = -sin(car.rotationAngle) * carSpeed * window.GetDeltaTime();
			motion.x = cos(car.rotationAngle) * carSpeed * window.GetDeltaTime();

			car.position += motion;
			car.rotationAngle += carHorizontalRotation * window.GetDeltaTime();
			
			if (CollisionUtility::SpherePoint(flag, car.position))
			{
				score++;
				flag.position = MovementUtility::FlagPosition(road, score);

				if (!(score % 4))
				{
					std::cout << "Time lap: " << glfwGetTime() - begin_lap << '\n';
					begin_lap = glfwGetTime();
				}
			}

			if (!CollisionUtility::RectangleRectangle(car, road))
			{
				car.position.y -= 800 * pow(window.GetDeltaTime(), 2);
			}

			if (car.position.y <= -20)
			{
				car.position = Vector3(4, 0, -2);
			}

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
				float animationSpeed = 0.01 * window.GetDeltaTime();
				animationT += animationSpeed;

				if (animationT > (12*window.GetDeltaTime()))
				{
					cameraIsBeingAnimated = false;
				}

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
				motion = motion * window.GetDeltaTime();


				float ypos = freeCamera.position.y;
				freeCamera.MoveCameraRelatively(motion);

				if (CollisionUtility::RectanglePoint(road, freeCamera.position - Vector3(0, freeCamera.position.y - road.position.y, 0)))
				{
					freeCamera.position.y = ypos;
				}
				

				if (CollisionUtility::RectanglePoint(car, freeCamera.position))
				{
					freeCamera.MoveCameraRelatively(-motion);
				}

			}
		}

		buttonPressedLastFrame = buttonPressed;

		window.PreDrawing(Color(1.0,1.0,1.0,1.0));
		window.DrawScene(scene1);
        window.PollEvents();
    }

	engine.Terminate();

    // Fim do programa
    return 0;
}