#include <shader.hpp>

void Shader::RefreshIllumination()
{
    GLuint light_position_id = glGetUniformLocation(program_id, "light_position"); // Posição da luz
    GLuint source_spectrum_id = glGetUniformLocation(program_id, "source_spectrum"); // Espectro da fonte de iluminação
    GLuint ambient_spectrum_id = glGetUniformLocation(program_id, "ambient_spectrum"); // Espectro da luz ambiente

    glm::vec4 light_position = { this->illumination.position.x, this->illumination.position.y, this->illumination.position.z, 1.0f };
    glm::vec4 source_spectrum = { this->illumination.lightSpectrum.x, this->illumination.lightSpectrum.y, this->illumination.lightSpectrum.z, 0.0f };
    glm::vec4 ambient_spectrum = { this->illumination.ambientSpectrum.x, this->illumination.ambientSpectrum.y, this->illumination.ambientSpectrum.z, 0.0f };

    glUniform4fv(light_position_id, 1, glm::value_ptr(light_position));
    glUniform4fv(source_spectrum_id, 1, glm::value_ptr(source_spectrum));
    glUniform4fv(ambient_spectrum_id, 1, glm::value_ptr(ambient_spectrum));
}

Shader::Shader(const char* vertex_shader_filename, const char* fragment_shader_filename)
{  
    this->illumination = LightSource();
    this->vertex_shader_id = Shader::LoadShader_Vertex(vertex_shader_filename);
    this->fragment_shader_id = Shader::LoadShader_Fragment(fragment_shader_filename);
    this->program_id = Engine::CreateGpuProgram(this->vertex_shader_id, this->fragment_shader_id);

    this->RefreshIllumination();
}

Shader::Shader()
{
    this->illumination = LightSource();
    this->vertex_shader_id = -1;
    this->fragment_shader_id = -1;
    this->program_id = -1;
}

// Função auxilar, utilizada pelas duas funções acima. Carrega código de GPU de
// um arquivo GLSL e faz sua compilação.
void Shader::LoadShader(const char* filename, GLuint shader_id)
{
    // Lemos o arquivo de texto indicado pela variável "filename"
    // e colocamos seu conteúdo em memória, apontado pela variável
    // "shader_string".
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    // Define o código do shader GLSL, contido na string "shader_string"
    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    // Compila o código do shader GLSL (em tempo de execução)
    glCompileShader(shader_id);

    // Verificamos se ocorreu algum erro ou "warning" durante a compilação
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    // Alocamos memória para guardar o log de compilação.
    // A chamada "new" em C++ é equivalente ao "malloc()" do C.
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    // Imprime no terminal qualquer erro ou "warning" de compilação
    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    // A chamada "delete" em C++ é equivalente ao "free()" do C
    delete [] log;
}

// Carrega um Vertex Shader de um arquivo GLSL. Veja definição de LoadShader() abaixo.
GLuint Shader::LoadShader_Vertex(const char* filename)
{
    // Criamos um identificador (ID) para este shader, informando que o mesmo
    // será aplicado nos vértices.
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    // Carregamos e compilamos o shader
    Shader::LoadShader(filename, vertex_shader_id);

    // Retorna o ID gerado acima
    return vertex_shader_id;
}

// Carrega um Fragment Shader de um arquivo GLSL . Veja definição de LoadShader() abaixo.
GLuint Shader::LoadShader_Fragment(const char* filename)
{
	// Criamos um identificador (ID) para este shader, informando que o mesmo
	// será aplicado nos fragmentos.
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Carregamos e compilamos o shader
	Shader::LoadShader(filename, fragment_shader_id);

	// Retorna o ID gerado acima
	return fragment_shader_id;
}

void Shader::SetIllumination(LightSource illumination)
{
    this->illumination = illumination;
}