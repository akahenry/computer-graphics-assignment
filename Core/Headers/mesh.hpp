#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector.hpp>
#include <iostream>
#include <tiny_obj_loader/tiny_obj_loader.h>
#include <tiny_obj_loader/stb_image.h>
#include <algorithm>

class Mesh
{
public:
	GLuint vaoId;
	bool usingTextureCoords = false;
	GLenum renderingMode = GL_TRIANGLES; // GL_TRIANGLES, GL_TRIANGLE_FAN ...
	int numVerticesComponents; // Quantidade de v�rtices*4, um float pra cada dimens�o
	int numNormalsComponents; // Quantidade de normais*4, um float pra cada dimens�o
	int numTextureComponents; // Quantidade de normais*2, um float pra cada dimens�o
	int numIndices; // Quantidade de indices no vetor indices
	Vector3 bbox_min;
	Vector3 bbox_max;

	/**
	 * Compute a mesh for box
	 * 
	 * @param[in] size a vector representing the size of the box
	 */
	void MakeBox(Vector3 size);

	/**
	 * Compute a mesh from a .obj file
	 * 
	 * @param[in] filename a string representing the .obj filename
	 * @param[in] basepath a string representing the base path to be used when searching for .mtl
	 */
	void LoadFromObj(const char* filename, const char* basepath = NULL);

private:
	GLfloat* model_coefficients; // Array com posi��es dos v�rtices
	GLfloat* normal_coefficients; // Array com normais dos vértices
	GLfloat* texture_coefficients; // Array com normais dos vértices
	GLfloat* color_coefficients; // Array com cores dos v�rtices
	GLuint* indices; // Array que define os tri�ngulos

	/**
	 * Computes the vertex array object, with its vertices, colors, textures, normals and indices
	 */
	void BindVao(); // com model_coefficients, color_coefficients, indices e rendering mode setados, constr�i o mesh e seta o vaoId
	
	/**
	 * Computes the normals from an object and set it in its components
	 * 
	 * @param[out] attrib the attributes of an object (vertices, normals)
	 * @param[out] shapes contains all the shapes of an object
	 * @param[out] materials contains all the constants related to the material of an object
	 */
	void ComputeNormals(tinyobj::attrib_t& attrib, std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& materials);
};

