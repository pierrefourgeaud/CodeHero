#version 330 core

in vec2 TexCoords;
in vec4 Color;

out vec4 color;

uniform sampler2D text;

void main()
{
    vec4 t = texture(text, TexCoords);
    if (t.r < 0.1)
        discard;
    color = vec4(Color.xyz, Color.w * t.r);
}