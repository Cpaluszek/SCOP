#version 330 core

in vec4 color;
in vec2 TexCoord;
in vec3 FragNormal;
in vec3 FragPos;

out vec4 FragColor;

uniform float textureTransitionFactor;
uniform sampler2D customTexture;

uniform int useLight;
uniform vec3 lightPos;

uniform vec3 viewPos;

/////////////////////
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float specularExponent;
uniform float dissolve;
uniform float refraction;

void main() {
    vec4 textureColor = texture(customTexture, TexCoord);

    vec4 finalColor = mix(color, textureColor, textureTransitionFactor);
    if (useLight == 0) {
        FragColor = finalColor;
    } else {
        // Diffuse
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(FragNormal, lightDir), 0.0);
        vec3 diffuse = diff * diffuseColor;

        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, FragNormal);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);
        vec3 specular = spec * specularColor;

        // Refraction
        vec3 refractDir = refract(-viewDir, FragNormal, refraction);
        vec2 distortedTexCoord = TexCoord + refractDir.xy * 0.1;
        vec4 refractedColor = texture(customTexture, distortedTexCoord);

        vec3 result = (ambientColor + diffuse + specular) * mix(vec3(color), vec3(refractedColor), textureTransitionFactor);
        FragColor = vec4(result, dissolve);
    }
}

