#include "Terrain.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Terrain::Terrain(glm::vec3 pos, glm::vec3 scale)
{
	m_pos = pos;
	m_scale = scale;

	vertexCount = 6;

	static unsigned int vbo, ibo;

	static float floor_cord[12] = {
		-0.5f, 0.0f, -0.50f,
		0.50f, 0.0f, -0.50f,
		0.50f, 00.0f, 0.50f,
		-0.50f, 00.0f, 0.50f
	};

	static unsigned int indices[6] = {
		0, 1, 2, // bl, br, tr
		2, 3, 0 // tr, tl, bl
	};

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), floor_cord, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	calculateTransformationMatrix();
}

void Terrain::calculateTransformationMatrix()
{
	glm::mat4 sc = glm::scale(glm::mat4(1), m_scale);
	glm::mat4 tr = glm::translate(glm::mat4(1), m_pos);
	transformationMatrix = tr * sc;
}