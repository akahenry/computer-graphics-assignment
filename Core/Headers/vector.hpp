#pragma once
#include <cmath>

class Vector3
{
	public:
		float x;
		float y;
		float z;

		/**
		 * Compute an instance of Vector3 class
		 * 
		 * @param[in] x a float representing the X component of the vector
		 * @param[in] y a float representing the Y component of the vector
		 * @param[in] z a float representing the Z component of the vector
		 * 
		 * @param[out] Vector3 an instance of Vector3
		 */
		Vector3(float x=0, float y=0, float z=0);

		/**
		 * Compute the norm of the vector (euclidean norm)
		 * 
		 * @param[out] norm a float representing the length of the vector 
		 */
		float Norm();

		/**
		 * Normalize the vector dividing each component for this vector norm (euclidean norm)
		 * 
		 * @param[out] vector an instance of Vector3 with the size equals to one
		 */
		Vector3 Normalized();

		/**
		 * Computes the cross product of two vectors, returning the vector based on the right-hand rule.
		 * 
		 * @param[in] other an instance of Vector3 to be used in the cross product calculation
		 * 
		 * @param[out] vector an instance of Vector3 with the size equals to one
		 */
		Vector3 CrossProduct(Vector3 other);

		/**
		 * Computes the dot product of two vectors, returning a float including the angle between these two vectors
		 * 
		 * @param[in] other an instance of Vector3 to be used
		 * 
		 * @param[out] float the operation's result
		 */
		float DotProduct(Vector3 other);

		/**
		 * Computes the projection of this vector on another
		 * 
		 * @param[in] other an instance of Vector3 to be used in the projection
		 * 
		 * @param[out] vector this vector projected onto the other vector
		 */
		Vector3 ProjectedOnto(Vector3 other);

		/**
		 * Computes the rejection of this vector on another
		 * 
		 * @param[in] other an instance of Vector3 to be used in the rejection
		 * 
		 * @param[out] vector this vector rejected onto the other vector
		 */
		Vector3 RejectedOnto(Vector3 other);

		/**
		 * Computes the sum between two vectors
		 * 
		 * @param[in] other an instance of Vector3 to be used in the sum
		 * 
		 * @param[out] vector an instance of Vector3 with each component added by each respective component in the other vector
		 */
		Vector3 operator+(const Vector3 other);
		Vector3& operator+=(const Vector3& other);

		/**
		 * Computes the difference between two vectors
		 * 
		 * @param[in] other an instance of Vector3 to be used in the difference
		 * 
		 * @param[out] vector an instance of Vector3 with each component subtracted by each respective component in the other vector
		 */
		Vector3 operator-(const Vector3 other);
		Vector3& operator-=(const Vector3& other);

		/**
		 * Computes the negative of a vector
		 * 
		 * @param[out] vector an instance of Vector3 with each component being its negative
		 */
		Vector3 operator-();

		/**
		 * Computes the quotient of a division between a vector and a number
		 * 
		 * @param[in] num a float number
		 * 
		 * @param[out] vector an instance of Vector3 with each component divided by the given number
		 */
		Vector3 operator/(float num);
		Vector3& operator/=(const Vector3& other);

		/**
		 * Computes the product of a multiplication between a vector and a number
		 * 
		 * @param[in] num a float number
		 * 
		 * @param[out] vector an instance of Vector3 with each component multiplicated by the given number
		 */
		Vector3 operator*(float num);
		Vector3& operator*=(const Vector3& other);
};

class Vector2
{
public:
	float x;
	float y;

	/**
	 * Compute an instance of Vector2 class
	 * 
	 * @param[in] x a float representing the X component of the vector
	 * @param[in] y a float representing the Y component of the vector
	 * 
	 * @param[out] Vector2 an instance of Vector2
	 */
	Vector2(float x = 0, float y = 0);

	/**
	 * Compute the norm of the vector (euclidean norm)
	 * 
	 * @param[out] norm a float representing the length of the vector 
	 */
	float Norm();

	/**
	 * Normalize the vector dividing each component for this vector norm (euclidean norm)
	 * 
	 * @param[out] vector an instance of Vector2 with the size equals to one
	 */
	Vector2 Normalized();

	/**
	 * Computes the dot product of two vectors, returning a float including the angle between these two vectors
	 * 
	 * @param[in] other an instance of Vector2 to be used
	 * 
	 * @param[out] float the operation's result
	 */
	float DotProduct(Vector2 other);

	/**
	 * Computes the sum between two vectors
	 * 
	 * @param[in] other an instance of Vector2 to be used in the sum
	 * 
	 * @param[out] vector an instance of Vector2 with each component added by each respective component in the other vector
	 */
	Vector2 operator+(const Vector2 other);
	Vector2& operator+=(const Vector2& other);

	/**
	 * Computes the difference between two vectors
	 * 
	 * @param[in] other an instance of Vector2 to be used in the difference
	 * 
	 * @param[out] vector an instance of Vector2 with each component subtracted by each respective component in the other vector
	 */
	Vector2 operator-(const Vector2 other);
	Vector2& operator-=(const Vector2& other);

	/**
	 * Computes the negative of a vector
	 * 
	 * @param[out] vector an instance of Vector2 with each component being its negative
	 */
	Vector2 operator-();

	/**
	 * Computes the quotient of a division between a vector and a number
	 * 
	 * @param[in] num a float number
	 * 
	 * @param[out] vector an instance of Vector2 with each component divided by the given number
	 */
	Vector2 operator/(float num);
	Vector2& operator/=(const Vector2& other);

	/**
	 * Computes the product of a multiplication between a vector and a number
	 * 
	 * @param[in] num a float number
	 * 
	 * @param[out] vector an instance of Vector2 with each component multiplicated by the given number
	 */
	Vector2 operator*(float num);
	Vector2& operator*=(const Vector2& other);
};