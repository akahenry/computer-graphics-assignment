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

	LightSource(Vector3 position = { 1,1,0.5 }, Vector3 lightSpectrum = { 1,1,1 }, Vector3 ambientSpectrum = { 0.2,0.2,0.2 }, LightType lightType = LightType::Phong);
};

#endif