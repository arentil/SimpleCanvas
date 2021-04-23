#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;      // actually this is not used because of the same Mesh class usage
layout(location = 2) in vec3 a_Color;       // actually this is not used because of the same Mesh class usage

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}