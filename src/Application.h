#pragma once

#include "EventManager.h"

class Application
{
protected:
	Application() {};

	static Application s_Application;

	//std::unordered_map<Model*, std::vector<Entity>> ntt_map;
	// future feature, instead of having a single entity

	bool isRunning = false;

	void resize();
	void close();
	void keyPressed(Event& e);

	float m_LastFrameTime = 0.0f;
public:
	Application(const Application&) = delete;
	static int Init();
	static void OnEvent();
	static void Update();
	static void Draw();
	static bool IsRunning();
	static void Delete();
};

