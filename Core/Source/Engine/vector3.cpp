#include <vector3.hpp>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::Norm()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::Normalized()
{
	return Vector3(x,y,z) / Norm();
}

Vector3 Vector3::CrossProduct(Vector3 other)
{
	float u1 = x;
	float u2 = y;
	float u3 = z;
	float v1 = other.x;
	float v2 = other.y;
	float v3 = other.z;

	return Vector3(
		u2 * v3 - u3 * v2,
		u3 * v1 - u1 * v3,
		u1 * v2 - u2 * v1
	);
}

float Vector3::DotProduct(Vector3 other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator+(const Vector3 other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator/(float num)
{
	return Vector3(x/num, y/num, z/num);
}