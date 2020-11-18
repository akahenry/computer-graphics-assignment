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

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D TextureImage;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool using_texture;
uniform bool render_as_black;

// Componentes de iluminação
uniform vec4 light_position; // Posição da luz
uniform vec3 source_spectrum; // Espectro da fonte de iluminação
uniform vec3 ambient_spectrum; // Espectro da luz ambiente
uniform vec3 diffuse_reflectance; // Refletância difusa
uniform vec3 specular_reflectance; // Refletância especular
uniform vec3 ambient_reflectance; // Refletância ambiente
uniform float phong_exponent; // Expoente especular para o modelo de iluminação de Phong
uniform bool gouraud_light; // Se a iluminação é gouraud ou não

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
    if (gouraud_light)
    {
        vec3 Kd = diffuse_reflectance; // 0.08, 0.4, 0.8
        vec3 Ks = specular_reflectance; // 0.8, 0.8, 0.8
        vec3 Ka = ambient_reflectance; // Kd/2
        float q = phong_exponent; // 32
    
        vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
        vec4 camera_position = inverse(view) * origin;
        vec4 p = position_world;

        vec4 n = normalize(normal);
        vec4 l = normalize(position_world - light_position); // 1.0,1.0,0.5,0.0
        vec4 v = normalize(camera_position - p);
        vec4 r = -l + 2*n*(dot(n, l));


        vec3 I = source_spectrum;
        vec3 Ia = ambient_spectrum;

        vec3 KdTexture = texture(TextureImage, texcoords).rgb;

        vec3 lambertDiffuse = Kd*I*max(0, dot(n, l));
        vec3 ambientTerm = Ka*Ia;
        vec3 phongSpecularTerm  = Ks*I*pow(max(0, dot(r, v)), q);

        if (using_texture)
        {
            vec3 colorInterpolada = vec3(lambertDiffuse*KdTexture + phongSpecularTerm + ambientTerm);
            colorInterpolada = pow(colorInterpolada, vec3(1.0,1.0,1.0)/2.2);
            cor_interpolada = vec4(colorInterpolada, 1.0);
        }
        else
        {
            vec3 colorInterpolada = vec3(cor_interpolada.x,
                                        cor_interpolada.y,
                                        cor_interpolada.z);

            cor_interpolada = vec4(lambertDiffuse*colorInterpolada + phongSpecularTerm + ambientTerm, cor_interpolada.w);
        }
    }
}