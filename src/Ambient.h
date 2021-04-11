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

class Camera
{
public:
	Camera(glm::vec3 pos)
		:m_Pos(pos)
	{};
	inline const glm::vec3& getPosition() const { return m_Pos; }
private:
	glm::vec3 m_Pos;
	Entity* player = nullptr;
};


