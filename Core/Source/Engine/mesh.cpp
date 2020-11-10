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

	this->ComputeNormals(attrib, shapes, materials);

	std::vector<GLuint> indices;
	std::vector<float> model_coefficients;
	std::vector<float> color_coefficients;
	std::vector<float> normal_coefficients;
	std::vector<float>  texture_coefficients;

	size_t num_triangles = shapes[0].mesh.num_face_vertices.size();

	for (size_t triangle = 0; triangle < num_triangles; ++triangle)
	{
		if (shapes[0].mesh.num_face_vertices[triangle] != 3)
			throw std::exception("ih rapaiz tem q ser tudo triangulo tlg");

		for (size_t vertex = 0; vertex < 3; ++vertex)
		{
			tinyobj::index_t idx = shapes[0].mesh.indices[3 * triangle + vertex];

			indices.push_back(3 * triangle + vertex);

			const float vx = attrib.vertices[3 * idx.vertex_index + 0];
			const float vy = attrib.vertices[3 * idx.vertex_index + 1];
			const float vz = attrib.vertices[3 * idx.vertex_index + 2];
			model_coefficients.push_back(vx); // X
			model_coefficients.push_back(vy); // Y
			model_coefficients.push_back(vz); // Z
			model_coefficients.push_back(1.0f); // W

			
			if (idx.normal_index != -1)
			{
				const float nx = attrib.normals[3 * idx.normal_index + 0];
				const float ny = attrib.normals[3 * idx.normal_index + 1];
				const float nz = attrib.normals[3 * idx.normal_index + 2];
				normal_coefficients.push_back(nx); // X
				normal_coefficients.push_back(ny); // Y
				normal_coefficients.push_back(nz); // Z
				normal_coefficients.push_back(0.0f); // W
			}
			else
			{
				const float nx = attrib.normals[3 * idx.vertex_index + 0];
				const float ny = attrib.normals[3 * idx.vertex_index + 1];
				const float nz = attrib.normals[3 * idx.vertex_index + 2];
				normal_coefficients.push_back(nx); // X
				normal_coefficients.push_back(ny); // Y
				normal_coefficients.push_back(nz); // Z
				normal_coefficients.push_back(0.0f); // W
			}

			if ( idx.texcoord_index != -1 )
			{
				const float u = attrib.texcoords[2*idx.texcoord_index + 0];
				const float v = attrib.texcoords[2*idx.texcoord_index + 1];
				texture_coefficients.push_back( u );
				texture_coefficients.push_back( v );
			}

			color_coefficients.push_back(0.0f);
			color_coefficients.push_back(0.0f);
			color_coefficients.push_back(1.0f);
			color_coefficients.push_back(1.0f);
		}
	}

	this->position = position;

	this->model_coefficients = model_coefficients.data();
	this->numVerticesComponents = model_coefficients.size();

	this->normal_coefficients = normal_coefficients.data();
	this->numNormalsComponents = normal_coefficients.size();

	this->texture_coefficients = texture_coefficients.data();
	this->numTextureComponents = texture_coefficients.size();

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

	// Faz as paradas das normais dos vértices e das faces. 
	if (this->numNormalsComponents)
    {
        GLuint VBO_normal_coefficients_id;
        glGenBuffers(1, &VBO_normal_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, this->numNormalsComponents * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, this->numNormalsComponents * sizeof(GLfloat), this->normal_coefficients);
        location = 2; // "(location = 2)" em "shader_vertex.glsl"
        number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

	// Faz as paradas das texturas
	if (this->numTextureComponents)
    {
        GLuint VBO_texture_coefficients_id;
        glGenBuffers(1, &VBO_texture_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, this->numTextureComponents*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, this->numTextureComponents*sizeof(GLfloat), this->texture_coefficients);
        location = 3; // "(location = 3)" em "shader_vertex.glsl"
        number_of_dimensions = 2; // vec2 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

	// Faz as paradas dos indices
	GLuint indices_id;
	glGenBuffers(1, &indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndices*sizeof(GLuint), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->numIndices*sizeof(GLuint), this->indices);
	
	glBindVertexArray(0);
}

void Mesh::ComputeNormals(tinyobj::attrib_t& attrib, std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& materials)
{
    if ( !attrib.normals.empty() )
        return;

    // Primeiro computamos as normais para todos os TRIÂNGULOS.
    // Segundo, computamos as normais dos VÉRTICES através do método proposto
    // por Gouraud, onde a normal de cada vértice vai ser a média das normais de
    // todas as faces que compartilham este vértice.

    size_t num_vertices = attrib.vertices.size() / 3;

    std::vector<int> num_triangles_per_vertex(num_vertices, 0);
    std::vector<Vector3> vertex_normals(num_vertices, Vector3(0.0f,0.0f,0.0f));

    for (tinyobj::shape_t shape : shapes)
    {
        size_t num_triangles = shape.mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(shape.mesh.num_face_vertices[triangle] == 3);

            Vector3 vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = shape.mesh.indices[3*triangle + vertex];
                const float vx = attrib.vertices[3*idx.vertex_index + 0];
                const float vy = attrib.vertices[3*idx.vertex_index + 1];
                const float vz = attrib.vertices[3*idx.vertex_index + 2];
                vertices[vertex] = Vector3(vx,vy,vz);
            }

            Vector3 a = vertices[0];
            Vector3 b = vertices[1];
            Vector3 c = vertices[2];

            Vector3 n = (a-c).CrossProduct(b-c);

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = shape.mesh.indices[3*triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] = vertex_normals[idx.vertex_index] + n;
				shape.mesh.indices[3*triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    attrib.normals.resize( 3*num_vertices );

    for (size_t i = 0; i < vertex_normals.size(); ++i)
    {
        Vector3 n = vertex_normals[i] / (float)num_triangles_per_vertex[i];
        n = n.Normalized();
        attrib.normals[3*i + 0] = n.x;
       	attrib.normals[3*i + 1] = n.y;
        attrib.normals[3*i + 2] = n.z;
    }
}