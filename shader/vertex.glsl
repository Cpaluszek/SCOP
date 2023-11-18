#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;
out vec2 TexCoord;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position /= gl_Position.w;       // Normalize homogeneous coordinates
    color = vec4(vertexColor, 1.0);
    TexCoord = texCoord;
}
