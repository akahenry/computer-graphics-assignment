#pragma once
class Color
{
public:
	float R;
	float G;
	float B;
	float A;

	/**
	 * Compute an instance of Color class.
	 *
	 * @param[in] R a float representing the value for the color's red component 
	 * @param[in] G a float representing the value for the color's green component 
	 * @param[in] B a float representing the value for the color's blue component 
	 * @param[in] A a float representing the value for the color's opacity 
	 * 
	 * @param[out] Color an instance of Color
	 */
	Color(float R, float G, float B, float A) : R(R), G(G), B(B), A(A) {};
};