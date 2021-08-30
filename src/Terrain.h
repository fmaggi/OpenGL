#pragma once
#include "Core.h"

// basic flat terrain

class Terrain 
{
public:
	Terrain(glm::vec3 pos, glm::vec3 scale);

	inline glm::vec3 getPos() { return m_pos; }
	inline glm::vec3 getScale() { return m_scale; }

	inline glm::mat4 getTransformationMAtrix() { return transformationMatrix; }
	void calculateTransformationMatrix();

	inline unsigned int getVaoID() { return vaoID; }
	inline unsigned int getCount() { return vertexCount; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::mat4 transformationMatrix;

	unsigned int vertexCount;
	unsigned int vaoID;
};

