#pragma once

#include "Entity.h"
#include "Shader.h"
#include "Ambient.h"
#include "Terrain.h"

class Renderer
{
public:
	Renderer() {};
	void render(Entity* ent, Shader& shader);
	void renderTerrain(Terrain* t, Shader& shader);

	void setClearColor(float r, float g, float b);

	inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }
	void setViewPort(int w, int h);
	inline void setCamera(Camera* cam) { m_camera = cam; }

	void prepare();
private:
	glm::mat4 m_projectionMatrix;
	Camera* m_camera = nullptr;
};

