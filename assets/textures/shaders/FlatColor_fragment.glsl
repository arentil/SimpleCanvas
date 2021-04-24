#version 330 core

in vec3 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform float u_Ambient;
uniform vec3 u_Diffuse;

out vec4 fragColor;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = u_Ambient * lightColor;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Diffuse - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * v_Color;

    fragColor = vec4(result, 1.0);
}