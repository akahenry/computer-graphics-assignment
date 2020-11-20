#pragma once

#include <vector.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#define PI 3.141592653589793238462643383279502884L

class Camera
{
public:
	Vector3 position; // posi��o no sistema de coordenadas global
	float nearPlane; // dist�ncia do centro de rota��o da c�mera at� o plano de near
	float farPlane; // dist�ncia do centro de rota��o da c�mera at� o plano de far
	float fov; // angulo do campo de vis�o da c�mera

	/**
	 * Compute an instance of Camera class.
	 *
	 * @param[in] position a vector representing the camera position
	 * @param[in] near a float representing the distance for the near plane
	 * @param[in] far a float representing the distance for the far plane
	 * @param[in] fov a float in [0, 2PI] representing the camera's fov
	 * 
	 * @param[out] Camera an instance of Camera
	 */
	Camera(Vector3 position, float near, float far, float fov);

	/**
	 * Compute view vector of this camera.
	 *
	 * @param[out] vector the view vector computed
	 */
	virtual Vector3 getViewVector() = 0;

	/**
	 * Compute the up vector relative from this camera.
	 *
	 * @param[out] vector the up vector computed
	 */
	Vector3 getRelativeUpVector(); // tamb�m conhecido como V

	/**
	 * Compute the right vector relative from this camera.
	 *
	 * @param[out] vector the right vector computed
	 */
	Vector3 getRelativeRightVector(); // tamb�m conhecido como U

	/**
	 * Compute the back vector relative from this camera.
	 *
	 * @param[out] vector the back vector computed
	 */
	Vector3 getRelativeBackVector(); // tamb�m conhecido como W

	/**
	 * Compute the right vector relative from this camera.
	 *
	 * @param[in] delta how much the camera will be moved
	 */
	void MoveCameraRelatively(Vector3 delta); // valores positivos do Vector3: direita, cima, frente
};

class FreeCamera : public Camera
{
public:
	float horizontalAngle; // rota��o do eixo vertical, vai de 0 a 2pi, 0 olha para z positivo
	float verticalAngle; // rota��o do eixo horizontal, vai de -pi/2 a pi/2, 0 olha para o horizonte

	/**
	 * Compute an instance of FreeCamera class.
	 *
	 * @param[in] position a vector representing the camera position
	 * @param[in] near a float representing the distance for the near plane
	 * @param[in] far a float representing the distance for the far plane
	 * @param[in] fov a float in [0, 2PI] representing the camera's fov
	 * @param[in] horizontalAngle a float representing the camera's angle with the horizontal axis
	 * @param[in] verticalAngle a float representing the camera's angle with the vertical axis
	 * 
	 * @param[out] FreeCamera an instance of FreeCamera
	 */
	FreeCamera(Vector3 position = Vector3(0, 0, 0), float near = -0.1f, float far = -10.0f, float fov = PI / 2, float horizontalAngle = PI, float verticalAngle = 0);
	
	/**
	 * Compute the camera horizontal and vertical angles
	 *
	 * @param[in] deltaAngle a vector with how much the camera will be turned in horizontal and vertical axis
	 */
	void MoveCameraAngle(Vector2 deltaAngle);

	/**
	 * Set the camera's view vector
	 *
	 * @param[in] view a vector to be used as the view vector of the camera
	 */
	void setViewVector(Vector3 view);

	/**
	 * Compute the camera's view vector based on the camera angles
	 *
	 * @param[out] Vector the camera's view vector
	 */
	Vector3 getViewVector();
};

class LookAtCamera : public Camera
{
public:
	Vector3 pointToLookAt; // ponto de look at

	/**
	 * Compute an instance of LookAtCamera class.
	 *
	 * @param[in] pointToLookAt a vector representing the look-at point
	 * @param[in] position a vector representing the camera position
	 * @param[in] near a float representing the distance for the near plane
	 * @param[in] far a float representing the distance for the far plane
	 * @param[in] fov a float in [0, 2PI] representing the camera's fov
	 * 
	 * @param[out] LookAtCamera an instance of LookAtCamera
	 */
	LookAtCamera(Vector3 pointToLookAt, Vector3 position = Vector3(0, 0, 0), float near = -0.1f, float far = -10.0f, float fov = PI / 2);

	/**
	 * Compute the camera's view vector based on the position and the look-at point
	 *
	 * @param[out] Vector the camera's view vector
	 */
	Vector3 getViewVector();
};