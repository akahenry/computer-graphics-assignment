#pragma once

#include <vector3.hpp>
#include <cmath>

class Camera
{
public:
	static const int TYPE_LOOK_AT = 0;
	static const int TYPE_FREE_CAMERA = 1;

	Vector3 position;
	float horizontalAngle; // rota��o do eixo vertical, vai de 0 a 2pi, 0 olha para y positivo
	float verticalAngle; // rota��o do eixo horizontal, vai de -pi/2 a pi/2, 0 olha para o horizonte
	float distance; // Dist�ncia do plano near da c�mera
	int lookType; // Look-At ou Free Camera

	Camera(Vector3 position=Vector3(0,0,0), float distance=1, float horizontalAngle=0, float verticalAngle=0, int lookType=Camera::TYPE_FREE_CAMERA);
	Vector3 getViewVector();
};