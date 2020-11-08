#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include <vector.hpp>

class LightSource
{
public:
    Vector3 position;
	Vector3 lightSpectrum;
	Vector3 ambientSpectrum;
    float phongSpecularExponent;

	LightSource(Vector3 position = { 1,1,0.5 }, Vector3 lightSpectrum = { 1,1,1 }, Vector3 ambientSpectrum = { 0.2,0.2,0.2 }, float phongExponent = 20);
};

#endif