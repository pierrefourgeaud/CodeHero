
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

struct BaseLight {
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

struct DirLight {
    vec3 direction;

    BaseLight base;
};

struct PointLight {
    vec3 position;

    // [0] = constant;
    // [1] = linear;
    // [2] = quadratic;
    float attenuation[3];

    BaseLight base;
};

uniform vec3 viewPos;
#if defined(NB_DIRECTIONAL_LIGHTS) && NB_DIRECTIONAL_LIGHTS > 0
uniform DirLight dirLights[NB_DIRECTIONAL_LIGHTS];
#endif
#if defined(NB_POINT_LIGHTS) && NB_POINT_LIGHTS > 0
uniform PointLight pointLights[NB_POINT_LIGHTS];
#endif
uniform Material material;

vec4 CalcLightBase(BaseLight light, vec3 lightDir, vec3 normal, vec3 viewDir) {
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec4 diffTex = texture(material.diffuse, TexCoords);
    #ifdef ALPHAMASK
        if (diffTex.a < 0.1) {
            discard;
        }
    #endif
    vec4 specTex = texture(material.specular, TexCoords);
    #ifdef ALPHAMASK
        if (specTex.a < 0.1) {
            discard;
        }
    #endif
    vec4 ambient = light.ambientIntensity * diffTex;
    vec4 diffuse = light.diffuseIntensity * diff * diffTex;
    vec4 specular = light.specularIntensity * spec * specTex;
    return (ambient + diffuse + specular);
}

// Calculates the color when using a directional light.
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    return CalcLightBase(light.base, normalize(-light.direction), normal, viewDir);
}

// Calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec4 color = CalcLightBase(light.base, normalize(light.position - fragPos), normal, viewDir);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = (light.attenuation[0] + light.attenuation[1] * distance + light.attenuation[2] * (distance * distance));

    return color / attenuation;
}
