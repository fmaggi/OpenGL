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

	inline void setProjectionMatrix(glm::mat4& mat) { projectionMatrix = mat; }

	void prepare();
private:
	glm::mat4 projectionMatrix;
};

