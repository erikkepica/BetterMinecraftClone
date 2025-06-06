#version 330 core

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 FragPos;
in mat3 TBN;

uniform vec4 col;
uniform sampler2D diffuseSampler;
uniform sampler2D specularSample;
uniform sampler2D normalSampler;

uniform float shininess;
uniform float specularStrength;
uniform float ambientStrength;
uniform vec3 ambientColor;
uniform float normalIntensity;

uniform vec3 lightColor;
uniform vec3 lightDir;
uniform float lightStrength;

uniform vec3 viewPos;

uniform float time;

void main()
{

    // Texture + color
    vec4 baseColor = texture(diffuseSampler, uv);
    vec3 objectColor = baseColor.rgb * col.rgb;

    // Ocean mask (specular map grayscale)
    float oceanMask = texture(specularSample, uv).r;

    // Sample normal map (tangent space)
    vec3 sampledNormal = texture(normalSampler, uv).rgb;
    sampledNormal = normalize(sampledNormal * 2.0 - 1.0); // [0,1]  [-1,1]

    // Blend with flat normal and apply normal intensity
    vec3 blendedNormal = normalize(mix(vec3(0.0, 0.0, 1.0), sampledNormal, normalIntensity));
    vec3 norm = normalize(TBN * blendedNormal); // To world space

    // Lighting
    vec3 lightDirection = normalize(-lightDir);
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    vec3 ambient = ambientStrength * ambientColor;

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor * lightStrength;

    float specMapVal = oceanMask;
    float specFactor = diff > 0.0 ? 1.0 : 0.0;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess)
           * lightStrength * specularStrength * specFactor;
    vec3 specular = specMapVal * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    if(baseColor.a != 1)
    {
        discard;
    }
    FragColor = vec4(result, baseColor.a);
}
