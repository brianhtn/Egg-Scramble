#version 330 core
layout (location = 0) in vec3 position;

layout (std140) uniform Matrices
{
    mat4 projection2;
    mat4 view2;
};

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 TexCoords;

void main()
{
    gl_Position =   projection * view * model * vec4(position, 1.0);
    gl_Position = gl_Position.xyww;
    TexCoords = position;
}