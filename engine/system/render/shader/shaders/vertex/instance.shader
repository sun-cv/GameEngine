#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in mat4 instanceModel;

out vec2 vTexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
   gl_Position = projection * view * instanceModel * vec4(position, 1.0);
   vTexCoord = texCoord;
}
