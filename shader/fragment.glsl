#version 330 core

in vec4 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform float textureTransitionFactor;
uniform sampler2D customTexture;

void main() {
    vec4 textureColor = texture(customTexture, TexCoord);

    vec4 finalColor = mix(color, textureColor, textureTransitionFactor);

    FragColor = finalColor;
}

