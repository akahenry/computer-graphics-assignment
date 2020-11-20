#pragma once

#include <mesh.hpp>
#include <texture.hpp>
#include <glm/mat4x4.hpp>

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
	Vector3 origin = Vector3(0, 0, 0);
    Texture texture;
    bool usingTexture = false;

    /**
	 * Compute an instance of GraphicObject class.
	 * 
	 * @param[in] position a Vector representing the object's position
	 * @param[in] mesh an instance of Mesh with all the shapes and mesh components for this object
	 * @param[in] reflectance the components related to the reflection constants of this object
	 * @param[in] phong a float representing the phong exponent used for this object
	 * 
	 * @param[out] GraphicObject an instance of GraphicObject
	 */
    GraphicObject(Vector3 position, Mesh* mesh, ReflectanceComponents reflectance, float phong);
    
    /**
	 * Set the mesh for the object
	 * 
	 * @param[in] mesh an instance of Mesh with all the shapes and mesh components for this object
	 */
    void SetMesh(Mesh* mesh);

    /**
	 * Set the texture for the object
	 * 
	 * @param[in] texture an instance of Texture with all components necessary to map the texture in this object
	 */
    void SetTexture(Texture texture);

    /**
	 * Set the texture for the object
	 * 
	 * @param[in] filename a string representing the name of the texture file
	 */
    void SetTexture(const char* filename);
};