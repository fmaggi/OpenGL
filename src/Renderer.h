#pragma once

#include "Core.h"
#include "Entity.h"
#include "Shader.h"
#include "Ambient.h"

class Renderer
{
public:
	Renderer();

	void renderModel(Model* model);
	void renderEntity(Entity* ent);
	void render(Entity* ent, Shader& shader);

	void setClearColor(float r, float g, float b);

	inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }
	void setViewPort(int w, int h);
	inline void setCamera(Camera* cam) { m_camera = cam; }

	void prepare();
private:
	glm::mat4 m_projectionMatrix;
	Camera* m_camera = nullptr;
};

