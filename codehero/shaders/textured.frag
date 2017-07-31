#version 330 core

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

    vec3 result = vec3(0.0, 0.0, 0.0);
#if defined(NB_DIRECTIONAL_LIGHTS) && NB_DIRECTIONAL_LIGHTS > 0
    for (int i = 0; i < NB_DIRECTIONAL_LIGHTS; i++) {
        result += CalcDirLight(dirLights[i], norm, viewDir);
    }
#endif

#if defined(NB_POINT_LIGHTS) && NB_POINT_LIGHTS > 0
    for (int i = 0; i < NB_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
#endif
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    color = vec4(result, 1.0);
}