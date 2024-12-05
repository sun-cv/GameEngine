#version 330 core

layout(location = 0) in vec2 aPos;      // Vertex position (x, y in screen space)
layout(location = 1) in vec2 aTexCoord; // Texture coordinate (u, v)

out vec2 TexCoord;

uniform mat4 projection;  // Projection matrix (e.g., orthographic for 2D)

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
