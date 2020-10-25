#pragma once

#include <glad/glad.h>
#include <vector3.hpp>

class Mesh
{
public:
	GLuint vaoId;
	Vector3 position;

	void MakeBox(Vector3 position, Vector3 size);

private:
	GLfloat* model_coefficients; // Array com posições dos vértices
	GLfloat* color_coefficients; // Array com cores dos vértices
	GLuint* indices; // Array que define os triângulos
	GLenum renderingMode; // GL_TRIANGLES, GL_TRIANGLE_FAN ...
	GLuint positionVBO; // VBO que guarda posições dos vértices

	void BindVao(); // com model_coefficients, color_coefficients, indices e rendering mode setados, constrói o mesh e seta o vaoId
};

