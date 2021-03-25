#include "Input.h"

void Move::execute(Entity* ntt, float ts)
{
	ntt->move(dir, ts);
}

void Rotate::execute(Entity* ntt, float ts)
{
	ntt->rotate(rot, ts);
}

Command* InputHandler::getCommand()
{
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) return keyW;
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) return keyA;
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) return keyS;
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) return keyD;

	return nullptr;
}

void InputHandler::handle(Entity* player, float ts)
{
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		keyW->execute(player, ts);
	}
	else if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		keyS->execute(player, ts);
	}

	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		keyA->execute(player, ts);
	}
	else if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		keyD->execute(player, ts);
	}	
}

InputHandler::InputHandler()
{
	keyW = new Move({ 0.0f, 0.5f, 0.0f });
	keyA = new Rotate({ 0.0f, 0.0f, 0.5f });
	keyS = new Move({ 0.0f, -0.5f, 0.0f });
	keyD = new Rotate({ 0.0f, 0.0f, -0.5f });
}

InputHandler::~InputHandler()
{
	delete keyA;
	delete keyD;
	delete keyS;
	delete keyW;
}
