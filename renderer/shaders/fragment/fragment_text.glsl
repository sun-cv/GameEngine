#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textTexture;  // Font texture (e.g., an atlas)
uniform vec3 textColor;         // Text color (RGB)
uniform float opacity;          // Optional: Transparency level

void main() {
    vec4 sampled = texture(textTexture, TexCoord); // Sample the texture
    FragColor = texture(textTexture, TexCoord) * vec4(textColor, opacity);
}
