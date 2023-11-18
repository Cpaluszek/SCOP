#version 330 core

in vec4 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform bool useTexture;
uniform sampler2D customTexture;

void main() {
    if (useTexture) {
        FragColor = texture(customTexture, TexCoord);
    } else {
        FragColor = color;
    }
}

