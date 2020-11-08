#include <object.hpp>

GraphicObject::GraphicObject(Mesh* mesh, ReflectanceComponents reflectance, float phong)
{
    this->mesh = mesh;
    this->reflectance = reflectance;
    this->phongExponent = phong;
}

void GraphicObject::SetMesh(Mesh* mesh)
{
    this->mesh = mesh;
}