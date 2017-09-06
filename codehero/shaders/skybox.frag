#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

// This sounds odd to have the skybox as a material.diffuse
struct Material {
  samplerCube diffuse;
};

uniform Material material;

void main()
{    
    FragColor = texture(material.diffuse, TexCoords);
}