#version 330 core

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 FragPos;
in mat3 TBN;

uniform vec4 col;
uniform sampler2D earth;
uniform sampler2D earthSpecular;
uniform sampler2D normalMapSampler;
uniform sampler2D noise;

uniform float shininess;
uniform float specularStrength;
uniform float ambientStrength;
uniform float normalIntensity;

uniform float waveStrength;
uniform float waveSpeed;
uniform float waveSize;

uniform vec3 lightColor;
uniform vec3 lightDir; // Direction *toward* the light
uniform float lightStrength;

uniform float time;

void main()
{
    vec3 viewPos = vec3(0, 0, 5);

    // Texture + color
    vec3 baseColor = texture(earth, uv).rgb;
    vec3 objectColor = baseColor * col.rgb;

    // Ocean mask (specular map grayscale)
    float oceanMask = texture(earthSpecular, uv).r;

    // Sample normal map (tangent space)
    vec3 sampledNormal = texture(normalMapSampler, uv).rgb;
    sampledNormal = normalize(sampledNormal * 2.0 - 1.0); // [0,1]  [-1,1]

    // === Distort Normals Directly (only in ocean areas) ===
    if (oceanMask > 0.2) {
        vec2 waveOffset = vec2(
            sin(time * waveSpeed),
            cos(time * waveSpeed * 0.8)
        );

        float wave = texture(noise, uv * waveSize + waveOffset).r+sin(uv.x)*0.2;

        sampledNormal.xy += vec2(wave, wave) * waveStrength;
        sampledNormal = normalize(sampledNormal);
    }

    // Blend with flat normal and apply normal intensity
    vec3 blendedNormal = normalize(mix(vec3(0.0, 0.0, 1.0), sampledNormal, normalIntensity));
    vec3 norm = normalize(TBN * blendedNormal); // To world space

    // Lighting
    vec3 lightDirection = normalize(-lightDir);
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = clamp(diff * lightColor * lightStrength, 0.0, 1.1);

    float specMapVal = oceanMask;
    float specFactor = diff > 0.0 ? 1.0 : 0.0;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess)
           * lightStrength * specularStrength * specFactor;
    vec3 specular = specMapVal * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, col.a);
}
