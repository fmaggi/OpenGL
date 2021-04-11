#pragma once
#include "Core.h"


class DisplayManager
{
public:
	DisplayManager() = default;

	int genereate(int width, int height, const std::string& title);

	inline GLFWwindow* getWindow() { return m_Window; }

	void resize(int w, int h);

	void update();
private:
	GLFWwindow* m_Window;
	const char* m_title;
	int m_height;
	int m_width;
	float aspectRatio;
};

