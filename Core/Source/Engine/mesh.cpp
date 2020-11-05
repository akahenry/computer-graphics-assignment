#include <mesh.hpp>

void Mesh::MakeBox(Vector3 position, Vector3 size)
{
	this->position = position;
	GLfloat model_coefficients[] = {
		// V�rtices da frente
		0 - size.x/2, 0 - size.y/2, 0 + size.z/2, 1.0f,
		0 + size.x/2, 0	- size.y/2, 0 + size.z/2, 1.0f,
		0 - size.x/2, 0 + size.y/2, 0 + size.z/2, 1.0f,
		0 + size.x/2, 0 + size.y/2, 0 + size.z/2, 1.0f,

		// V�rtices de tr�s
		0 - size.x/2, 0	- size.y/2, 0 - size.z/2, 1.0f,
		0 + size.x/2, 0	- size.y/2, 0 - size.z/2, 1.0f,
		0 - size.x/2, 0 + size.y/2, 0 - size.z/2, 1.0f,
		0 + size.x/2, 0 + size.y/2, 0 - size.z/2, 1.0f,
	};
	this->model_coefficients = model_coefficients;
	this->numVerticesComponents = sizeof(model_coefficients) / sizeof(model_coefficients[0]);

	// TODO: lidar com cores direito
	GLfloat color_coefficients[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};
	this->color_coefficients = color_coefficients;

	GLuint indices[] = {
		// frente
		0, 1, 2,
		2, 1, 3,
		// tr�s
		6, 5, 4,
		7, 5, 6,
		// cima
		2, 3, 6,
		6, 3, 7,
		// baixo
		4, 1, 0,
		5, 1, 4,
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

void Mesh::LoadFromObj(Vector3 position, const char* filename, const char* basepath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, true);

	if (!err.empty())
		fprintf(stderr, "\n%s\n", err.c_str());

	if (!ret)
		throw std::runtime_error("Erro ao carregar modelo.");

	std::vector<GLuint> indices;
	std::vector<float> model_coefficients;
	std::vector<float> color_coefficients;

	size_t first_index = indices.size();
	size_t num_triangles = shapes[0].mesh.num_face_vertices.size();

	for (size_t triangle = 0; triangle < num_triangles; ++triangle)
	{
		if (shapes[0].mesh.num_face_vertices[triangle] != 3)
			throw std::exception("ih rapaiz tem q ser tudo triangulo tlg");

		for (size_t vertex = 0; vertex < 3; ++vertex)
		{
			tinyobj::index_t idx = shapes[0].mesh.indices[3 * triangle + vertex];

			indices.push_back(first_index + 3 * triangle + vertex);

			const float vx = attrib.vertices[3 * idx.vertex_index + 0];
			const float vy = attrib.vertices[3 * idx.vertex_index + 1];
			const float vz = attrib.vertices[3 * idx.vertex_index + 2];
			model_coefficients.push_back(vx); // X
			model_coefficients.push_back(vy); // Y
			model_coefficients.push_back(vz); // Z
			model_coefficients.push_back(1.0f); // W

			color_coefficients.push_back(0.0f);
			color_coefficients.push_back(0.0f);
			color_coefficients.push_back(1.0f);
			color_coefficients.push_back(1.0f);
		}
	}

	this->position = position;

	this->model_coefficients = model_coefficients.data();
	this->numVerticesComponents = model_coefficients.size();

	this->color_coefficients = color_coefficients.data();

	this->indices = indices.data();
	this->numIndices = indices.size();

	renderingMode = GL_TRIANGLES;

	this->BindVao();
}

void Mesh::BindVao()
{
	GLuint location;
	GLint number_of_dimensions = 4;

	// Faz as paradas das posi��es dos v�rtices
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

	// Faz as paradas das cores dos v�rtices
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