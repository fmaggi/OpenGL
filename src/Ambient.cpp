#include "Ambient.h"

glm::mat4 Camera::getTransformationMatrix()
{
	viewMatrix = glm::lookAt(m_Pos, player->getPosition(), glm::vec3(0, 1, 0));
	return viewMatrix;
}

void Camera::move(glm::vec3 d)
{
	m_Pos.x += -d.x;
	m_Pos.y += d.y;
	m_Pos.z += -d.z;
}
