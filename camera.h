#pragma once

#include "vector3.h"
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
	Vector3 getViewVector();
	int lookType; // Look-At ou Free Camera
};