#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texCoord;
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex, 1.0);
    TexCoords = texCoord;
}
