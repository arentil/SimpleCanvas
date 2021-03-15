#version 330 core

layout(location = 0) out vec4 a_color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    a_color = texture(u_Texture, v_TexCoord);
}