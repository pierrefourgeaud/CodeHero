
#ifndef NB_POINT_LIGHTS
#define NB_POINT_LIGHTS 0
#endif

#ifndef NB_SPOT_LIGHTS
#define NB_SPOT_LIGHTS 0
#endif

#ifndef NB_DIRECTIONAL_LIGHTS
#define NB_DIRECTIONAL_LIGHTS 0
#endif

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

uniform vec3 viewPos;
#if defined(NB_DIRECTIONAL_LIGHTS) && NB_DIRECTIONAL_LIGHTS > 0
uniform DirLight dirLights[NB_DIRECTIONAL_LIGHTS];
#endif
#if defined(NB_POINT_LIGHTS) && NB_POINT_LIGHTS > 0
uniform PointLight pointLights[NB_POINT_LIGHTS];
#endif
uniform Material material;

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient = light.ambientIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specularIntensity * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    vec3 ambient = light.ambientIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specularIntensity * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
