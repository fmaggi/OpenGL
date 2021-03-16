#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::renderModel(Model* model)
{
	glBindVertexArray(model->getVaoID());
	unsigned int attrib = model->getAttribs();
	unsigned int i = 0;
	do
	{
		glEnableVertexAttribArray(i);
		i++;
	} while (i < attrib);
	auto m = model->getMeshes();
	for (ObjModel* obj : m)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->getIbo());
		glDrawElements(GL_TRIANGLES, obj->getVertexCount(), GL_UNSIGNED_INT, 0);
	}
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

