#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

// take in the fragpos
in vec3 FragPos;

// take in normal value from vertex shader
in vec3 Normal;

void main()
{
    // ambient strength
    float ambientStrength = 0.25f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // final output
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}