#version 330 core

struct DirectionalLight
{
    vec3 _direction;
    vec3 _color;
    float ambientIntensity;
    float diffuseIntensity;
};

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

in vec3 FragPos;
in vec3 Normal;

void main()
{    
    color = vec4(texture(texture_diffuse1, TexCoords));
}