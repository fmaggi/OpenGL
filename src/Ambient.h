#pragma once
#include "Core.h"
#include "Entity.h"
#include "BaseObject.h"

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

class Camera : public BaseObject
{
public:
	Camera(glm::vec3 pos)
		:m_Position(pos)
	{
		viewMatrix = glm::lookAt(m_Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		m_Rotation = { 0.0f, 0.0f, 0.0f };
	}

	inline void setPlayer(Entity* p) { player = p; }

	inline void setPosition(glm::vec3&& position) override { m_Position = position; }
	inline glm::vec3 getPosition() const override { return m_Position; }
	void move(glm::vec3 d) override;

	inline void setRotation(glm::vec3&& rot) override { m_Rotation = rot; }
	inline glm::vec3 getRotation() const override { return m_Rotation; }
	inline void rotate(glm::vec3 d) override { m_Rotation += d; }

	glm::mat4 getViewMatrix();
private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	glm::mat4 viewMatrix;

	Entity* player = nullptr;
};


