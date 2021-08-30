#include "Input.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Move::execute(BaseObject* ntt, float ts)
{
	ntt->move(dir * ts);
}

void Rotate::execute(BaseObject* ntt, float ts)
{
	ntt->rotate(rot * ts);
}

void InputHandler::changeInput()
{	
	bool a = false;
	bool d = false;
	bool m = false;
	bool r = false;
	while (!a && !d)
	{
		glfwPollEvents();
		a = (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS);
		d = (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS);
	}
	while (!r && !m)
	{
		glfwPollEvents();
		r = (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS);
		m = (glfwGetKey(m_Window, GLFW_KEY_M) == GLFW_PRESS);
	}
	if (a)
	{
		delete keyA;
		if (m)
		{
			keyA = new Move({ -1.0f, 0.0f, 0.0f });
			return;
		}
		else if (r)
		{
			keyA = new Rotate({ 0.0f, 0.0f, 0.5f });
			return;
		}
	}
	if (d)
	{
		delete keyD;
		if (m)
		{
			keyD = new Move({ 1.0f, 0.0f, 0.0f });
			return;
		}
		else if (r)
		{
			keyD = new Rotate({ 0.0f, 0.0f, -0.5f });
			return;
		}
	}

}

void InputHandler::handle(BaseObject* player, float ts)
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
	keyW = new Move({ 0.0f, 2.0f, 0.0f });
	keyA = new Move({ -2.0f, 0.0f, 0.0f });
	keyS = new Move({ 0.0f, -2.0f, 0.0f });
	keyD = new Move({ 2.0f, 0.0f, 0.0f });
	m_Window = nullptr;
}

InputHandler::~InputHandler()
{
	delete keyA;
	delete keyD;
	delete keyS;
	delete keyW;
}
