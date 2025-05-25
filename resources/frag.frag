#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 FragPos;

uniform vec4 col;
uniform sampler2D tex;

uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightDir; // Changed from lightPos to lightDir (directional light)
uniform float lightStrength;

void main()
{
    // Sample texture color (object's base color)
    vec3 objectColor = vec3(texture(tex, uv)*col);

    // Ambient lighting
    vec3 ambient = ambientStrength * lightColor;

    // Normalize inputs
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(-lightDir); // Light coming *from* the direction

    // Diffuse lighting
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor * lightStrength;

    // Combine results
    vec3 result = clamp((ambient + diffuse),0,1.2) * objectColor;
    FragColor = vec4(result, 1.0);
}