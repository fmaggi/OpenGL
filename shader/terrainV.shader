#version 400 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0);
    gl_Position = proj * view * worldPos;
    //gl_Position = vec4(position, 1.0);
}