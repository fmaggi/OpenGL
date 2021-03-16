#pragma once

#include "Core.h"
#include "Entity.h"
#include "Ambient.h"

class Renderer
{
public:
	Renderer();

	inline void setLight(Light* light) { m_Light = light; }

	void renderModel(Model* model);
	void renderEntity(Entity* ent);

	void prepare();
private:
	Light* m_Light;
};

