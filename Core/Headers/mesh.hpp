#pragma once

#include <glad/glad.h>
#include <vector.hpp>
#include <iostream>
#include <tiny_obj_loader/tiny_obj_loader.h>
#include <tiny_obj_loader/stb_image.h>
#include <algorithm>

class Mesh
{
public:
	GLuint vaoId;
	Vector3 position;
	Vector3 scale = Vector3(1, 1, 1);
	float rotationAngle = 0;
	Vector3 rotationAxis = Vector3(0,1,0);
	GLenum renderingMode = GL_TRIANGLES; // GL_TRIANGLES, GL_TRIANGLE_FAN ...
	int numVerticesComponents; // Quantidade de vértices*4, um float pra cada dimensão
	int numIndices; // Quantidade de indices no vetor indices

	void MakeBox(Vector3 position, Vector3 size);
	void LoadFromObj(Vector3 position, const char* filename, const char* basepath = NULL);

private:
	GLfloat* model_coefficients; // Array com posições dos vértices
	GLfloat* color_coefficients; // Array com cores dos vértices
	GLuint* indices; // Array que define os triângulos

	void BindVao(); // com model_coefficients, color_coefficients, indices e rendering mode setados, constrói o mesh e seta o vaoId
};

