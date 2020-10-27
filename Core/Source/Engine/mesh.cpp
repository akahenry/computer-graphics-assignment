#include <mesh.hpp>

void Mesh::MakeBox(Vector3 position, Vector3 size)
{
	this->position = position;
	GLfloat model_coefficients[] = {
		// Vértices da frente
		0		  , 0		  , 0, 1.0f,
		0 + size.x, 0		  , 0, 1.0f,
		0		  , 0 + size.y, 0, 1.0f,
		0 + size.x, 0 + size.y, 0, 1.0f,

		// Vértices de trás
		0		  , 0		  , 0 + size.z, 1.0f,
		0 + size.x, 0		  , 0 + size.z, 1.0f,
		0		  , 0 + size.y, 0 + size.z, 1.0f,
		0 + size.x, 0 + size.y, 0 + size.z, 1.0f,
	};
	this->model_coefficients = model_coefficients;
	this->numVerticesComponents = sizeof(model_coefficients) / sizeof(model_coefficients[0]);

	// TODO: lidar com cores direito
	GLfloat color_coefficients[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};
	this->color_coefficients = color_coefficients;

	GLuint indices[] = {
		// frente
		0, 1, 2,
		2, 1, 3,
		// trás
		4, 5, 6,
		6, 5, 7,
		// cima
		2, 3, 6,
		6, 3, 7,
		// baixo
		0, 1, 4,
		4, 1, 5,
		// esquerda
		4, 0, 6,
		6, 0, 2,
		// direita
		1, 5, 3,
		3, 5, 7
	};
	this->indices = indices;
	this->numIndices = sizeof(indices) / sizeof(indices[0]);

	this->renderingMode = GL_TRIANGLES;

	this->BindVao();
}

void Mesh::BindVao()
{
	GLuint location;
	GLint number_of_dimensions = 4;

	// Faz as paradas das posições dos vértices
	GLuint VBO_model_coefficients_id;
	glGenBuffers(1, &VBO_model_coefficients_id);
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId); // Aqui que ele faz o bind do vaoId do mesh
	glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
	glBufferData(GL_ARRAY_BUFFER, this->numVerticesComponents*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->numVerticesComponents*sizeof(GLfloat), this->model_coefficients);
	location = 0;
	number_of_dimensions = 4;
	glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Faz as paradas das cores dos vértices
	GLuint VBO_color_coefficients_id;
	glGenBuffers(1, &VBO_color_coefficients_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
	glBufferData(GL_ARRAY_BUFFER, this->numVerticesComponents * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->numVerticesComponents * sizeof(GLfloat), this->color_coefficients);
	location = 1;
	number_of_dimensions = 4;
	glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Faz as paradas dos indices
	GLuint indices_id;
	glGenBuffers(1, &indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndices*sizeof(GLuint), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->numIndices*sizeof(GLuint), this->indices);
	glBindVertexArray(0);
}