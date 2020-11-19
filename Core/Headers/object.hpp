#pragma once

#include <mesh.hpp>
#include <texture.hpp>

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
    Vector3 position;
	Vector3 scale = Vector3(1, 1, 1);
	float rotationAngle = 0;
    Vector3 rotationAxis = Vector3(0,1,0);
    Texture texture;
    bool usingTexture = false;

    
    GraphicObject(Vector3 position, Mesh* mesh, ReflectanceComponents reflectance, float phong);
    void SetMesh(Mesh* mesh);
    void SetTexture(Texture texture);
    void SetTexture(const char* filename);
};