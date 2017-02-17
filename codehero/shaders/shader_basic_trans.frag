#version 330 core

#include "lighting.frag"

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    color = mix(
                texture(ourTexture1, TexCoord).rgba,
                texture(ourTexture2, TexCoord).rgba,
                vec4(texture(ourTexture2, TexCoord)).a * 0.4);
}
