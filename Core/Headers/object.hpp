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

    GraphicObject(Mesh* mesh);
    void SetMesh(Mesh* mesh);
};