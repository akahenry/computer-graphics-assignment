#include <camera.hpp>

Camera::Camera(int lookType, Vector3 position, Vector3 pointToLookAt, float near, float far, float fov, float horizontalAngle, float verticalAngle)
{
	this->position = position;
	this->horizontalAngle = horizontalAngle;
	this->verticalAngle = verticalAngle;
	this->lookType = lookType;
	this->nearPlane = near;
	this->farPlane = far;
	this->fov = fov;

	if (this->lookType == Camera::TYPE_LOOK_AT)
	{
		this->pointToLookAt = pointToLookAt;
	}
}

Vector3 Camera::getViewVector()
{
	float vx = cos(this->verticalAngle) * sin(this->horizontalAngle);
	float vz = cos(this->verticalAngle) * cos(this->horizontalAngle);
	float vy = sin(this->verticalAngle);

	if (this->lookType == Camera::TYPE_FREE_CAMERA)
	{
		return Vector3(vx, vy, vz);
	}
	
	if (this->lookType == Camera::TYPE_LOOK_AT)
	{
		return this->pointToLookAt - this->position;
	}
}

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