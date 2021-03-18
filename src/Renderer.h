#pragma once

#include "Core.h"
#include "Entity.h"
#include "Ambient.h"

class Renderer
{
public:
	Renderer();

	void renderModel(Model* model);
	void renderEntity(Entity* ent);

	void prepare();
};

