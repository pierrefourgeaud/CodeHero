
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

// [0->2] = Position
// [3->5] = ambient/diffuse/specular
// [6->8] = constant/linear/quadratic
#define PointLight mat3

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
    BaseLight base;
    base.ambientIntensity = light[1][0];
    base.diffuseIntensity = light[1][1];
    base.specularIntensity = light[1][2];
    vec4 color = CalcLightBase(base, normalize(light[0] - fragPos), normal, viewDir);
    // Attenuation
    float distance = length(light[0] - fragPos);
    float attenuation = (light[2][0] + light[2][1] * distance + light[2][2] * (distance * distance));

    return color / attenuation;
}
