#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::renderModel(Model* model)
{
	glBindVertexArray(model->getVaoID());
	auto m = model->getMeshes();
	for (ObjModel* obj : m)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->getIbo());
		glDrawElements(GL_TRIANGLES, obj->getVertexCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::render(Entity* ent, Shader& shader)
{
	Model* model = ent->getModel();
	glm::mat4 trans = ent->getTransformationMatrix();
	auto meshes = model->getMeshes();
	shader.bind();
	shader.setUniformM4f("model", trans);
	shader.setUniformM4f("proj", projectionMatrix);
	glBindVertexArray(model->getVaoID());
	for (ObjModel* obj : meshes)
	{
		Material material = model->getMaterial(obj->getMaterial());
		shader.setUniformMaterial("material", material);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->getIbo());
		glDrawElements(GL_TRIANGLES, obj->getVertexCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::setClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderEntity(Entity* ent)
{
	Model* model = ent->getModel();
	renderModel(model);
}


void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

