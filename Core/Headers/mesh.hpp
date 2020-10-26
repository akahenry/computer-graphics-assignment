#pragma once

#include <glad/glad.h>
#include <vector3.hpp>

class Mesh
{
public:
	GLuint vaoId;
	Vector3 position;
	Vector3 scale = Vector3(1, 1, 1);
	float rotationAngle = 0;
	Vector3 rotationAxis = Vector3(0,1,0);
	GLenum renderingMode = GL_TRIANGLES; // GL_TRIANGLES, GL_TRIANGLE_FAN ...
	int numIndices; // Quantidade de indices no vetor indices

	void MakeBox(Vector3 position, Vector3 size);

private:
	GLfloat* model_coefficients; // Array com posi��es dos v�rtices
	GLfloat* color_coefficients; // Array com cores dos v�rtices
	GLuint* indices; // Array que define os tri�ngulos

	void BindVao(); // com model_coefficients, color_coefficients, indices e rendering mode setados, constr�i o mesh e seta o vaoId
};

