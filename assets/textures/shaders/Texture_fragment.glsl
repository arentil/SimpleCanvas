#version 330 core

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
    fragColor = texture(u_Texture, v_TexCoord);
}