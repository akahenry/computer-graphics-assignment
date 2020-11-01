#pragma once

#include <vector.hpp>
#include <cmath>
#define PI 3.141592653589793238462643383279502884L

class Camera
{
public:
	Vector3 position; // posição no sistema de coordenadas global
	float nearPlane; // distância do centro de rotação da câmera até o plano de near
	float farPlane; // distância do centro de rotação da câmera até o plano de far
	float fov; // angulo do campo de visão da câmera

	Camera(Vector3 position, float near, float far, float);

	virtual Vector3 getViewVector() = 0;
	Vector3 getRelativeUpVector(); // também conhecido como V
	Vector3 getRelativeRightVector(); // também conhecido como U
	Vector3 getRelativeBackVector(); // também conhecido como W
	void MoveCameraRelatively(Vector3 delta); // valores positivos do Vector3: direita, cima, frente
};

class FreeCamera : public Camera
{
public:
	float horizontalAngle; // rotação do eixo vertical, vai de 0 a 2pi, 0 olha para z positivo
	float verticalAngle; // rotação do eixo horizontal, vai de -pi/2 a pi/2, 0 olha para o horizonte

	FreeCamera(Vector3 position = Vector3(0, 0, 0), float near = -0.1f, float far = -10.0f, float fov = PI / 2, float horizontalAngle = PI, float verticalAngle = 0);
	void MoveCameraAngle(Vector2 deltaAngle);

	Vector3 getViewVector();
};

class LookAtCamera : public Camera
{
public:
	Vector3 pointToLookAt; // ponto de look at

	LookAtCamera(Vector3 pointToLookAt, Vector3 position = Vector3(0, 0, 0), float near = -0.1f, float far = -10.0f, float fov = PI / 2);

	Vector3 getViewVector();
};