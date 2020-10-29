#pragma once

#include <vector3.hpp>
#include <cmath>
#define PI 3.141592653589793238462643383279502884L

class Camera
{
public:
	static const int TYPE_LOOK_AT = 0;
	static const int TYPE_FREE_CAMERA = 1;

	Vector3 position;
	float horizontalAngle; // rotação do eixo vertical, vai de 0 a 2pi, 0 olha para z positivo
	float verticalAngle; // rotação do eixo horizontal, vai de -pi/2 a pi/2, 0 olha para o horizonte
	float nearPlane; // distância do centro de rotação da câmera até o plano de near
	float farPlane; // distância do centro de rotação da câmera até o plano de far
	float fov; // angulo do campo de visão da câmera
	int lookType; // look-At ou Free Camera

	Camera(Vector3 position=Vector3(0,0,0), float near=-0.1f, float far=-10.0f, float fov=PI/2, float horizontalAngle=PI, float verticalAngle=0, int lookType=Camera::TYPE_FREE_CAMERA);
	Vector3 getViewVector();
	// também conhecido como V
	Vector3 getRelativeUpVector();
	// também conhecido como U
	Vector3 getRelativeRightVector();
	// também conhecido como W
	Vector3 getRelativeBackVector();
};