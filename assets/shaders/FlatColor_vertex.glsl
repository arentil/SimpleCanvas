#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform mat4 u_ModelInvT;

out vec3 v_Normal;
out vec3 v_FragPos;
out vec3 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    v_Normal = mat3(u_ModelInvT) * a_Normal;
    
}