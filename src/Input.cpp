#include "Input.h"

InputHandler InputHandler::s_Input;


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
	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_W) == GLFW_PRESS) return s_Input.keyW;
	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_A) == GLFW_PRESS) return s_Input.keyA;
	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_S) == GLFW_PRESS) return s_Input.keyS;
	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_D) == GLFW_PRESS) return s_Input.keyD;

	return nullptr;
}

void InputHandler::handle(Entity* player, float ts)
{
	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		s_Input.keyW->execute(player, ts);
	}
	else if (glfwGetKey(s_Input.m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		s_Input.keyS->execute(player, ts);
	}

	if (glfwGetKey(s_Input.m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		s_Input.keyA->execute(player, ts);
	}
	else if (glfwGetKey(s_Input.m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		s_Input.keyD->execute(player, ts);
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
