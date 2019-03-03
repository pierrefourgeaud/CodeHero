
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
    #ifdef SPECULARMAP
        sampler2D specular;
    #endif
    sampler2D opacity;
    float shininess;
    vec2 textureCoordsOffset;
};

// [0] = ambient, [1] = diffuse, [2] = specular intensities
#define BaseLight vec3
// [0] = direction, [1] = BaseLight
#define DirLight mat2x3
// [0] = Position, [1] = BaseLight, [2] = constant/linear/quadratic
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
    #ifdef DIFFUSEMAP
        vec4 diffTex = texture(material.diffuse, GetTexCoords(material.textureCoordsOffset));
        #ifdef ALPHAMASK
            if (diffTex.a < 0.01) {
                discard;
            }
        #endif
    #else
        // TODO(pierre): We should support diffuse color when loading material
        vec4 diffTex = vec4(1.0, 1.0, 1.0, 1.0);
    #endif
    vec4 ambient = light[0] * diffTex;
    vec4 diffuse = light[1] * diff * diffTex;

    #ifdef SPECULARMAP
        vec4 specTex = texture(material.specular, GetTexCoords(material.textureCoordsOffset));
    #else
        vec4 specTex = vec4(0.0, 0.0, 0.0, 1.0);
    #endif

    vec4 specular = light[2] * spec * specTex;
    return (ambient + diffuse + specular);
}

// Calculates the color when using a directional light.
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    return CalcLightBase(light[1], normalize(-light[0]), normal, viewDir);
}

// Calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec4 color = CalcLightBase(light[1], normalize(light[0] - fragPos), normal, viewDir);
    // Attenuation
    float distance = length(light[0] - fragPos);
    float attenuation = (light[2][0] + light[2][1] * distance + light[2][2] * (distance * distance));

    return color / attenuation;
}
