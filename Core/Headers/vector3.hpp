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
};

