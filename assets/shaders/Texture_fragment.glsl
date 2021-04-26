#version 330 core

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_Texture;

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
    int shiness = 32;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiness);
    vec3 specular = u_Specular * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(texture(u_Texture, v_TexCoord));
    fragColor = vec4(result, 1.0);
}