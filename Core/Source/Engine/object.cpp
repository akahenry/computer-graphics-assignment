#include <object.hpp>

GraphicObject::GraphicObject(Mesh* mesh)
{
    this->mesh = mesh;
}

void GraphicObject::SetMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

void GraphicObject::AddOnWindow(Window* window)
{
    window->DrawMesh(*(this->mesh));
}