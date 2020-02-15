#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
   vertexColor = vec4(abs(aPos.x), abs(aPos.y), abs(aPos.z), 1.0);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
