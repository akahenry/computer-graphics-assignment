#include <light.hpp>

LightSource::LightSource(Vector3 position, Vector3 lightSpectrum, Vector3 ambientSpectrum, LightType lightType) :
	position(position),
	lightSpectrum(lightSpectrum),
	ambientSpectrum(ambientSpectrum),
	lightType(lightType) {}