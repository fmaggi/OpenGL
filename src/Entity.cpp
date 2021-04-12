#include "Entity.h"

static float GRAVITY = -9.8;
// TODO: physics file


Entity::Entity()
{
	m_Speed = { 0.0f, 0.0f };
	m_Mass = 10;
	m_Power = 0;
	m_Acceleration =  0.0f;
	m_Model = NULL;
	m_Position = { 0.0f, 0.0f, 0.0f };
	m_Rotation = { 0.0f, 0.0f, 0.0f };
	m_Scale = { 1.0f, 1.0f, 1.0f };
}

Entity::~Entity()
{
}

void Entity::launch()
{
	if (m_Power)
	{
		m_Power = 0;
		return;
	}
	m_Power = 130;
}

void Entity::calculateTransformationMatrix()
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 ViewRotateX = glm::rotate(glm::mat4(1.0f),
		m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotateY = glm::rotate(
		ViewRotateX,
		m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot = glm::rotate(ViewRotateY, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

	m_transformation = trans * rot * scale;
}
