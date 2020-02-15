#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;    
uniform float time;
out vec4 vertexColor;
void main()
{
   vertexColor = vec4(aCol.x*cos(10*time), aCol.y*sin(10*time), aCol.z*cos(10*time)*sin(7*time), 1.0);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
