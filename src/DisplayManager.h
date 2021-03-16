#pragma once
#include "Core.h"
#include "EventManager.h"

class DisplayManager
{
public:
	DisplayManager() = default;

	int genereate(int width, int height, const std::string& title);

	void resize(int w, int h);

	inline const glm::mat4& getPojectionMatrix() const { return projectionMatrix; }

	inline GLFWwindow* getWindow() { return m_Window; }

	void update();
private:
	GLFWwindow* m_Window;
	const char* m_title;
	int m_height;
	int m_width;
	float aspectRatio;

	glm::mat4 projectionMatrix;
};

