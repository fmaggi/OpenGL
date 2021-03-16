#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 toLightVector;
out vec3 surfaceNormal;

uniform vec3 LightPos;

uniform mat4 proj;
uniform mat4 model;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0);

    toLightVector = LightPos - worldPos.xyz;
    surfaceNormal = (model * vec4(normal, 0.0)).xyz;

    gl_Position = proj * worldPos;
}