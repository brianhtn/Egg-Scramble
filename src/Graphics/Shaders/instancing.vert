#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instanceMatrix;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

//uniform mat4 projection;
//uniform mat4 view;

out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * instanceMatrix * vec4(position, 1.0f); 
    TexCoords = texCoords;
}