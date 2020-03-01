#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = normalize(transpose(inverse(mat3(model)))*vNormal);
    Position = vec3(model * vec4(vPosition, 1));
    TexCoords = vTexCoords;
    gl_Position = projection * view * model * vec4(vPosition, 1);
}