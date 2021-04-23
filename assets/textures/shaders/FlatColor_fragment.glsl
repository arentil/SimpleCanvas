#version 330 core

layout(location = 0) out vec4 a_color;

in vec4 v_Color;

void main()
{
    a_color = v_Color;
}