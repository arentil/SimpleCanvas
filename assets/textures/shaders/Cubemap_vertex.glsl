#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 TexCoords;

void main()
{
    TexCoords = aPos;
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
}