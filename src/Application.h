#pragma once
#include "Renderer.h"
#include "DisplayManager.h"
#include "OBJLoader.h"
#include "Shader.h"
#include "EventManager.h"

class Application
{
protected:
	Application() {};

	static Application s_Application;
	Renderer m_Renderer;
	DisplayManager m_Display;

	//std::unordered_map<Model*, std::vector<Entity>> ntt_map;
	// future feature, instead of having a single entity

	Entity* player;
	Shader shader;

	GLFWwindow* window;
	bool isRunning;

	void resize();
	void close();
	void keyPressed(Events& e);

	float m_LastFrameTime = 0.0f;
public:
	Application(const Application&) = delete;
	static int Init();
	static void Event();
	static void Update();
	static void Draw();
	static bool IsRunning();
	static void Delete();
};

