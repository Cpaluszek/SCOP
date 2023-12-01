#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in vec2 texCoord;

out vec4 color;
out vec2 TexCoord;
out vec3 FragNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position /= gl_Position.w;       // Normalize homogeneous coordinates

    TexCoord = texCoord;
    color = vec4(vertexColor, 1.0);

    FragPos = vec3(model * vec4(position, 1.0));
    
    FragNormal = normalize(normal);
    // FragNormal = normalize( mat3(transpose(inverse(model))) * normal);
}
