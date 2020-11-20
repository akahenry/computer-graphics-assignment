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

	float animationT = 0; // a anima��o de transi��o de primeira pra terceira pessoa usa um t de 0 a 1
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
		// Mostra ou esconde o mouse se a tela ta selecionada
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

		// Começa a usar a freeCamera
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

		// Começa a usar a look-at camera
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

		// A look-at tem o ponto que ela está olhando atualizado todo frame para a posição do carro
		if (isLookAt)
		{
			lookAtCamera.pointToLookAt = car.position;

			// O carro só pode se mover quando for a camera look-at
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

			// Rotaciona o carro para ter um movimento mais intuitivo
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
			

			// Verifica se o carro pegou algum checkpoint
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

			// Mantém o carro em cima da pista
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

			// A posição da camera é atualizada de acordo com a rotação do carro, para ter uma camera mais intuitiva
			lookAtCamera.position = {
				car.position.x - 5 * cos(car.rotationAngle + relativeLookAtHorizontalRotation),
				car.position.y + 5,
				car.position.z + 5 * sin(car.rotationAngle + relativeLookAtHorizontalRotation)
			};
		}
		// Free Camera
		else
		{
			// Est� na transi��o de teceira e primeira pessoa
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

				// Verifica se a posição da camera tem intersecção com a pista, impedindo que a camera atravesse a pista
				if (CollisionUtility::RectanglePoint(road, freeCamera.position - Vector3(0, freeCamera.position.y - road.position.y, 0)))
				{
					freeCamera.position.y = ypos;
				}
				
				// Verifica se a posição da camera tem intersecção com o carro, impedindo que a camera atravesse o carro
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