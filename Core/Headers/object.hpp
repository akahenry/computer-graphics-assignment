#pragma once

#include <mesh.hpp>

struct ReflectanceComponents
{
    Vector3 diffuse;
    Vector3 specular;
    Vector3 ambient;
};

class GraphicObject
{
public:
    Mesh* mesh;
    ReflectanceComponents reflectance;
    float phongExponent;

    GraphicObject(Mesh* mesh, ReflectanceComponents reflectance, float phong);
    void SetMesh(Mesh* mesh);
};