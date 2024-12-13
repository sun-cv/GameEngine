#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 color; // Add a uniform for color

void main() {
    vec4 texColor = texture(texture1, TexCoord);
    FragColor = texColor * vec4(color, 1.0);
}
