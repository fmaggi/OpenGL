#pragma once

#include "Core.h"
#include "Entity.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();

	void renderModel(Model* model);
	void renderEntity(Entity* ent);
	void render(Entity* ent, Shader& shader);

	void setClearColor(float r, float g, float b);

	void prepare();
};

