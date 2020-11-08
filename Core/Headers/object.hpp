#pragma once

#include <mesh.hpp>
#include <window.hpp>

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
    void AddOnWindow(Window* window);
    void SetMesh(Mesh* mesh);
};