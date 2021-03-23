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
	glm::vec3 dir;
};

class Rotate : public Command
{
public:
	Rotate(glm::vec3&& r)
		: rot(r)
	{};
	void execute(Entity* ntt, float ts) override;
	glm::vec3 rot;
};

class InputHandler
{
public:
	InputHandler(const InputHandler&) = delete;
	static Command* getCommand();
	inline static void setWindow(GLFWwindow* window) { s_Input.m_Window = window; }
private:
	~InputHandler();
	InputHandler();
	GLFWwindow* m_Window;

	static InputHandler s_Input;

	Command* keyW;
	Command* keyA;
	Command* keyS;
	Command* keyD;
};
