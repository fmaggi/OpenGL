#include "Physics.h"

#include "glm/glm.hpp"
#include <glm/gtx/matrix_decompose.hpp>


namespace Physics
{
	const static float GRAVITY = -9.8f;
	const static float FLOOR = 0.0f;

	void update(Entity* ntt, float ts)
	{
		glm::vec2 m_speed = ntt->getSpeed();
		glm::vec3 rotation = ntt->getRotation();
		glm::vec3 m_pos = ntt->getPosition();

		float cosZ = glm::cos(rotation.z);
		float sinZ = glm::sin(rotation.z);

		float normal = GRAVITY * -1 * (m_pos.y == FLOOR);
		float acceleration_y = GRAVITY + (ntt->getPower() * cosZ)/ntt->getMass() + normal;
		float acceleration_x = (ntt->getPower() * sinZ) / ntt->getMass();

		float speed_y = m_speed.y + acceleration_y * ts;
		float speed_x = m_speed.x + acceleration_x * ts;

		float move_y = m_speed.y * ts + 0.5 * acceleration_y * ts * ts;
		float move_x = m_speed.x * ts + 0.5 * acceleration_x * ts * ts;

		if (m_pos.y + move_y <= FLOOR)
		{
			ntt->setPosition(glm::vec3(m_pos.x, FLOOR, m_pos.z));
			ntt->setSpeed(0, 0);
			return;
		}

		ntt->move(glm::vec3(-move_x, move_y, 0.0f));

		ntt->setSpeed(speed_x, speed_y);
	}
}
