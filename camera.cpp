#include "camera.h"

Vector3 Camera::getViewVector()
{
	float r = this->distance;
	float vx = r * cos(this->verticalAngle) * sin(this->horizontalAngle);
	float vz = r * cos(this->verticalAngle) * cos(this->horizontalAngle);
	float vy = r * sin(this->verticalAngle);

	if (this->lookType == Camera::TYPE_FREE_CAMERA)
	{
		return Vector3(-vx, -vy, -vz);
	}
}