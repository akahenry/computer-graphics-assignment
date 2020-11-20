#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include <vector.hpp>

enum class LightType { Phong, Gouraud};

class LightSource
{
public:
    Vector3 position;
	Vector3 lightSpectrum;
	Vector3 ambientSpectrum;
	LightType lightType;

	/**
	 * Compute an instance of LightSource class.
	 * 
	 * @param[in] position a Vector representing the light's position
	 * @param[in] lightSpectrum a Vector representing the light's spectrum
	 * @param[in] ambientSpectrum a Vector representing the ambient spectrum (default value to be add when calculating colors)
	 * @param[in] lightType an instance of LightType representing if the light interpolates using Gouraud (vertex) or Phong (point) algorithm
	 * 
	 * @param[out] LightSource an instance of LightSource
	 */
	LightSource(Vector3 position = { 1,1,0.5 }, Vector3 lightSpectrum = { 1,1,1 }, Vector3 ambientSpectrum = { 0.2,0.2,0.2 }, LightType lightType = LightType::Phong);
};

#endif