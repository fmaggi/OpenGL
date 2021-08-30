#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Renderer::render(Entity* ent, Shader& shader)
{
	Model* model = ent->getModel();
	auto meshes = model->getMeshes();
	glm::mat4 trans = ent->getTransformationMatrix();
	glm::mat4 view = m_camera->getViewMatrix();
	shader.bind();
	shader.setUniformM4f("model", trans);
	shader.setUniformM4f("proj", m_projectionMatrix);
	shader.setUniformM4f("view", view);

	glBindVertexArray(model->getVaoID());
	for (ObjModel* obj : meshes)
	{
		Material material = model->getMaterial(obj->getMaterial());
		shader.setUniformMaterial("material", material);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->getIbo());
		glDrawElements(GL_TRIANGLES, obj->getVertexCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::renderTerrain(Terrain* t, Shader& shader)
{
	glBindVertexArray(t->getVaoID());
	shader.bind();

	glm::mat4 model = t->getTransformationMAtrix();
	glm::mat4 view = m_camera->getViewMatrix();

	shader.setUniformM4f("proj", m_projectionMatrix);
	shader.setUniformM4f("view", view);
	shader.setUniformM4f("model", model);

	glDrawElements(GL_TRIANGLES, t->getCount(), GL_UNSIGNED_INT, 0);
}


void Renderer::setClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::setViewPort(int w, int h)
{
	m_projectionMatrix = glm::perspective(45.0f, (float)w / h, 0.1f, 100.0f);
	glViewport(0, 0, w, h);
}
	

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

