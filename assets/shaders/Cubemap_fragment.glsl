#version 450 core

in vec3 v_TexCoord;
uniform samplerCube skybox;

out vec4 fragColor;

void main()
{    
    fragColor = texture(skybox, v_TexCoord);
}