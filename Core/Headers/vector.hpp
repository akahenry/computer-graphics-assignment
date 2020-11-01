#pragma once
#include <cmath>

class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3(float x=0, float y=0, float z=0);
		float Norm();
		Vector3 Normalized();
		Vector3 CrossProduct(Vector3 other);
		float DotProduct(Vector3 other);
		Vector3 operator+(const Vector3 other);
		Vector3 operator-(const Vector3 other);
		Vector3 operator-();
		Vector3 operator/(float num);
		Vector3 operator*(float num);
};

class Vector2
{
public:
	float x;
	float y;

	Vector2(float x = 0, float y = 0);
	float Norm();
	Vector2 Normalized();
	float DotProduct(Vector2 other);
	Vector2 operator+(const Vector2 other);
	Vector2 operator-(const Vector2 other);
	Vector2 operator-();
	Vector2 operator/(float num);
	Vector2 operator*(float num);
};