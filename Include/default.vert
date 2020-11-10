#version 330 core

// Atributos de vértice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a função BuildTriangle() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 color_coefficients;
layout (location = 2) in vec4 normal_coefficients;
layout (location = 3) in vec2 texture_coefficients;

// Atributos de vértice que serão gerados como saída ("out") pelo Vertex Shader.
// ** Estes serão interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais serão recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
out vec4 cor_interpolada;
out vec4 normal;
out vec4 position_world;
out vec2 texcoords;
out vec4 position_model;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool render_as_black;

void main()
{
    gl_Position = projection * view * model * model_coefficients;

    position_world = model * model_coefficients;

    position_model = model_coefficients;

    if ( render_as_black )
    {
        // Ignoramos o atributo cor dos vértices, colocando a cor final como
        // preta. Utilizamos isto para renderizar as arestas pretas dos cubos.
        cor_interpolada = vec4(0.0f,0.0f,0.0f,1.0f);
    }
    else
    {
        cor_interpolada = color_coefficients;

        normal = inverse(transpose(model)) * normal_coefficients;
        normal.w = 0.0;

        texcoords = texture_coefficients;
    }
}