#include "Input.h"
#include "DisplayManager.h"

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

InputHandler::InputHandler()
{
	keyW = new Move({ 0.0f, 0.5f, 0.0f });
	keyA = new Rotate({ 0.0f, 0.0f, 0.5f });
	keyS = new Move({ 0.0f, -0.5f, 0.0f });
	keyD = new Rotate({ 0.0f, 0.0f, -0.5f });
}

InputHandler::~InputHandler()
{
	std::cout << "Deleted Input" << std::endl;
	delete keyA;
	delete keyD;
	delete keyS;
	delete keyW;
}
