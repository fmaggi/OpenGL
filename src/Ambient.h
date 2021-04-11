#pragma once
#include "Core.h"
#include "Entity.h"

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 col)
		: m_Position(pos), m_Color(col)
	{};
	inline const glm::vec3& getPosition() const { return m_Position; }
	inline const glm::vec3& getColor() const { return m_Color; }
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
};

class Camera : public Entity
{
public:
	Camera(glm::vec3 pos)
		:m_Pos(pos)
	{
		viewMatrix = glm::lookAt(m_Pos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	inline void setPlayer(Entity* p) { player = p; }

	inline const glm::vec3& getPosition() const { return m_Pos; }
	glm::mat4 getTransformationMatrix() override;
	void move(glm::vec3 d) override;
private:
	glm::vec3 m_Pos;

	glm::mat4 viewMatrix;

	Entity* player = nullptr;
};


