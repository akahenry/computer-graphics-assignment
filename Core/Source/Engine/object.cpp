#include <object.hpp>

GraphicObject::GraphicObject(Vector3 position, Mesh* mesh, ReflectanceComponents reflectance, float phong)
{
    this->position = position;
    this->mesh = mesh;
    this->reflectance = reflectance;
    this->phongExponent = phong;
}

void GraphicObject::SetMesh(Mesh* mesh)
{
    this->mesh = mesh;
}