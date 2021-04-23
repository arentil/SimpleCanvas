#version 330 core

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
    float ambientStrength = 0.3;
    vec3 result = ambientStrength * vec3(texture(u_Texture, v_TexCoord));
    fragColor = vec4(result, 1.0);
}