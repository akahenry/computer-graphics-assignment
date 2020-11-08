#include <light.hpp>

LightSource::LightSource(Vector3 position, SpectrumComponents spectrum, float phongExponent)
{
    this->position = position;
    this->spectrumComponents = spectrumComponents;
    this->phongSpecularExponent = phongExponent;
}