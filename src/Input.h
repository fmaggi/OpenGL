#pragma once
#include "Core.h"
#include "BaseObject.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(BaseObject* ntt, float ts) = 0;
};

class Move : public Command
{
public:
	Move(glm::vec3&& d)
		: dir(d)
	{};
	void execute(BaseObject* ntt, float ts) override;
private:
	glm::vec3 dir;
};

class Rotate : public Command
{
public:
	Rotate(glm::vec3&& r)
		: rot(r)
	{};
	void execute(BaseObject* ntt, float ts) override;
private:
	glm::vec3 rot;
};

class InputHandler
{
public:
	~InputHandler();
	InputHandler();

	inline void setWindow(GLFWwindow* window) { m_Window = window; }
	void changeInput();
	void handle(BaseObject* player, float ts);
private:
	GLFWwindow* m_Window;

	Command* keyW;
	Command* keyA;
	Command* keyS;
	Command* keyD;
};
