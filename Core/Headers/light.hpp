#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include <vector.hpp>

struct SpectrumComponents
{
    Vector3 source;
    Vector3 ambient;
};

class LightSource
{
public:
    Vector3 position;
    SpectrumComponents spectrumComponents;
    float phongSpecularExponent;

    LightSource(Vector3 position, SpectrumComponents spectrum, float phongExponent);
};

#endif