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

	LightSource(Vector3 position = { 0,0,0 }, Vector3 lightSpectrum = { 1,1,1 }, Vector3 ambientSpectrum = { 1,1,1 }, float phongExponent = 20);
};

#endif