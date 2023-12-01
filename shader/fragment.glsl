#version 330 core

in vec4 color;
in vec2 TexCoord;
in vec3 FragNormal;
in vec3 FragPos;

out vec4 FragColor;

uniform float textureTransitionFactor;
uniform sampler2D customTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

void main() {
    // vec4 textureColor = texture(customTexture, TexCoord);
    //
    // vec4 finalColor = mix(color, textureColor, textureTransitionFactor);

    // FragColor = finalColor;

    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(FragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, FragNormal);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // vec3 result = (ambient + diffuse ) * objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}

