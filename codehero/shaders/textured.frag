#version 330 core

#define NB_DIRECTIONAL_LIGHTS 1
#define NB_POINT_LIGHTS 1

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

#include "lighting.frag"

void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result;
    for(int i = 0; i < NB_DIRECTIONAL_LIGHTS; i++)
      result += CalcDirLight(dirLights[i], norm, viewDir);
    for(int i = 0; i < NB_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    color = vec4(result, 1.0);
}
