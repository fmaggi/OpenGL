#include "Ambient.h"

glm::mat4 Camera::getViewMatrix()
{
	viewMatrix = glm::lookAt(m_Position, player->getPosition(), glm::vec3(0, 1, 0));
	return viewMatrix;
}

void Camera::move(glm::vec3 d)
{
	m_Position.x += d.x;
	m_Position.y += d.y;
	m_Position.z += d.z;
}
