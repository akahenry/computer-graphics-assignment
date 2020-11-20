#include <camera.hpp>

Vector3 Camera::getRelativeBackVector()
{
	Vector3 view = getViewVector();
	return (-view).Normalized();
}

Vector3 Camera::getRelativeRightVector()
{
	Vector3 w = getRelativeBackVector();
	Vector3 up = Vector3(0, 1, 0);
	return up.CrossProduct(w).Normalized();
}

Vector3 Camera::getRelativeUpVector()
{
	return getRelativeBackVector().CrossProduct(getRelativeRightVector());
}

void Camera::MoveCameraRelatively(Vector3 delta)
{
	position = position + getRelativeRightVector() * delta.x + getRelativeUpVector() * delta.y + getRelativeBackVector() * delta.z * -1;
}

Camera::Camera(Vector3 position, float near, float far, float fov)
{
	this->position = position;
	this->nearPlane = near;
	this->farPlane = far;
	this->fov = fov;
}

FreeCamera::FreeCamera(Vector3 position, float near, float far, float fov, float horizontalAngle, float verticalAngle) : Camera(position, near, far, fov)
{
	this->horizontalAngle = horizontalAngle;
	this->verticalAngle = verticalAngle;
}

Vector3 FreeCamera::getViewVector()
{
	float vx = cos(this->verticalAngle) * sin(this->horizontalAngle);
	float vz = cos(this->verticalAngle) * cos(this->horizontalAngle);
	float vy = sin(this->verticalAngle);

	return Vector3(vx, vy, vz);
}

LookAtCamera::LookAtCamera(Vector3 pointToLookAt, Vector3 position, float near, float far, float fov) : Camera(position, near, far, fov)
{
	this->pointToLookAt = pointToLookAt;
}

Vector3 LookAtCamera::getViewVector()
{
	return this->pointToLookAt - this->position;
}

void FreeCamera::MoveCameraAngle(Vector2 deltaAngle)
{
	horizontalAngle += deltaAngle.x;
	verticalAngle += deltaAngle.y;
}

void FreeCamera::setViewVector(Vector3 view)
{
	this->horizontalAngle = atan2(view.Normalized().x, view.Normalized().z);
	this->verticalAngle = asin(view.Normalized().y);
}