#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

layout (location = 3) in mat4 instanceMatrix;
out vec2 vTexCoord;

uniform mat4 MVP;

void main()
{
   gl_Position = MVP * instanceMatrix * vec4(position, 1.0);
   vTexCoord = texCoord;
};