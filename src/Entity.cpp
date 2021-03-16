#include "Entity.h"

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
		move(glm::vec3(0.5f, 0.0f, 0.0f), timestep);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		move(glm::vec3(-0.5f, 0.0f, 0.0f), timestep);
	}
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
