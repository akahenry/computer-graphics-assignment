#include <object.hpp>

GraphicObject::GraphicObject(Vector3 position, Mesh* mesh, ReflectanceComponents reflectance, float phong)
{
    this->position = position;
    this->mesh = mesh;
    this->reflectance = reflectance;
    this->phongExponent = phong;
    this->texture = Texture();
    this->usingTexture = false;
}

void GraphicObject::SetMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

void GraphicObject::SetTexture(Texture texture)
{
    this->usingTexture = true;
    this->texture = texture;
}

void GraphicObject::SetTexture(const char* filename)
{
    this->SetTexture(Texture(filename));
}