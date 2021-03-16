#version 400 core

in vec3 toLightVector;
in vec3 surfaceNormal;

out vec4 Color;

uniform vec3 LightColor;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLight = normalize(toLightVector);

	float dotP = dot(unitNormal, unitLight);
	float brightness = max(dotP, 0.1);

	vec3 diffuse = brightness * LightColor;
	
	Color = vec4(diffuse, 1.0) * vec4(0.64, 0.64, 0.64, 1.0);
	//Color = vec4(diffuse, 1.0) * vec4(unitNormal, 1.0);
}