#include "Entity.h"


Entity::Entity()
{
	m_Speed = 0.0f;
	m_Mass = 10;
	m_Power = 0;
	m_Acceleration = 0;
	m_Model = NULL;
	m_Position = { 0.0f, 0.0f, 0.0f };
	m_Rotation = { 0.0f, 0.0f, 0.0f };
	m_Scale = { 1.0f, 1.0f, 1.0f };
}

Entity::~Entity()
{
    delete m_Model;
}

void Entity::update(float timestep, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		move(glm::vec3(0.0f, -0.5f, 0.0f), timestep);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		move(glm::vec3(0.0f, 0.5f, 0.0f), timestep);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		rotate(glm::vec3(0.0f, 0.0f, -0.5f), timestep);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		rotate(glm::vec3(0.0f, 0.0f, 0.5f), timestep);
	}

	m_Speed += m_Acceleration * timestep;

	m_Position.x += -(m_Speed * glm::sin(m_Rotation.z)) * timestep;
	m_Position.y += (m_Speed * glm::cos(m_Rotation.z)) * timestep;
}

void Entity::launch()
{
	m_Power = 130;
	float weight = m_Mass * -9.8;
	m_Acceleration = m_Power + weight;
}

glm::mat4 Entity::getTransformationMatrix()
{
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,
        m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 ViewRotateY = glm::rotate(
        ViewRotateX,
        m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 trans = glm::rotate(ViewRotateY, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

	return scale * trans;
}
