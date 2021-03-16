#pragma once
#include "Core.h"

enum class EventType
{
	None = 0,
	Resize, WinClose,
	KeyPressed,
	Done
};

class Events
{
public:
	Events(EventType t)
		: type(t)
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	};

	inline EventType getType() { return type; }
	bool handled = false;
	
	int data[3];
	std::unordered_map<std::string, int> dataMap;

private:
	EventType type = EventType::None;
};

class EventManager
{
public:
	EventManager(const EventManager&) = delete;
	static void dispatch(Events t);
	static std::vector<Events>& pollEvents();
	static void handled();
private:
	EventManager() {};

	std::vector<Events> m_events;
	static EventManager s_EventManager;

	void KeyPressed();
};


