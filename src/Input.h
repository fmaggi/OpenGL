#pragma once
#include "Entity.h"
#include "Core.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Entity* ntt, float ts) = 0;
};

class Move : public Command
{
public:
	Move(glm::vec3&& d)
		: dir(d)
	{};
	void execute(Entity* ntt, float ts) override;
private:
	glm::vec3 dir;
};

class Rotate : public Command
{
public:
	Rotate(glm::vec3&& r)
		: rot(r)
	{};
	void execute(Entity* ntt, float ts) override;
private:
	glm::vec3 rot;
};

class InputHandler
{
public:
	~InputHandler();
	InputHandler();

	Command* getCommand();
	inline void setWindow(GLFWwindow* window) { m_Window = window; }
	void handle(Entity* player, float ts);
private:
	GLFWwindow* m_Window;

	Command* keyW;
	Command* keyA;
	Command* keyS;
	Command* keyD;
};
