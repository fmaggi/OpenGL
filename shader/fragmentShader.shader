#version 400 core

in vec3 toLightVector;
in vec3 surfaceNormal;

out vec4 Color;

struct Material
{
	float ns;
	vec3 ka;
	vec3 ks;
	vec3 kd;
	vec3 ke;
	float ni;
	float d;
	float illum;
};

uniform vec3 LightColor;
uniform vec3 baseColor;

uniform Material material;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLight = normalize(toLightVector);

	float dotP = dot(unitNormal, unitLight);
	float brightness = max(dotP, 0.1);

	vec3 diffuse = brightness * LightColor;
	
	//Color = vec4(1.0, 0.0, 0.0, 1.0);
	Color = vec4(diffuse, 1.0) * vec4(material.kd, 1.0);
	//Color = vec4(diffuse, 1.0) * vec4(unitNormal, 1.0);
}