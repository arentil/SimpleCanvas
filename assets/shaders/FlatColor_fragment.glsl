#version 450 core

in vec3 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform float u_Ambient;
uniform vec3 u_Diffuse;
uniform float u_Specular;
uniform vec3 u_ViewPos;

out vec4 fragColor;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // ambient
    vec3 ambient = u_Ambient * lightColor;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Diffuse - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float theta = max(dot(viewDir, reflectDir), 0.0);
    int shiness = 32;
    float shine = pow(theta, shiness);
    vec3 specular = u_Specular * shine * lightColor;

    vec3 result = (ambient + diffuse + specular) * v_Color;
    fragColor = vec4(result, 1.0);
}