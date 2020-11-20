#include <vector.hpp>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

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

Vector3 Vector3::ProjectedOnto(Vector3 other)
{
	return other.Normalized() * this->DotProduct(other.Normalized());
}
Vector3 Vector3::RejectedOnto(Vector3 other)
{
	Vector3 p = this->ProjectedOnto(other);
	return Vector3(this->x - p.x, this->y - p.y, this->z - p.z);
}

Vector3 Vector3::operator+(const Vector3 other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3 other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator/(float num)
{
	return Vector3(x/num, y/num, z/num);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

Vector3 Vector3::operator*(float num)
{
	return Vector3(x * num, y * num, z * num);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

/***************** Vector2 *********************/

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::Norm()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalized()
{
	return Vector2(x, y) / Norm();
}

float Vector2::DotProduct(Vector2 other)
{
	return x * other.x + y * other.y;
}

Vector2 Vector2::operator+(const Vector2 other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2 other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator/(float num)
{
	return Vector2(x / num, y / num);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

Vector2 Vector2::operator*(float num)
{
	return Vector2(x * num, y * num);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}