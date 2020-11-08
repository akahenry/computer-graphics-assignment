#include <light.hpp>

LightSource::LightSource(Vector3 position, Vector3 lightSpectrum, Vector3 ambientSpectrum, float phongExponent) :
	position(position),
	lightSpectrum(lightSpectrum),
	ambientSpectrum(ambientSpectrum),
	phongSpecularExponent(phongSpecularExponent) {}