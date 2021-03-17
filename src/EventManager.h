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
	{};

	inline EventType getType() { return type; }
	bool handled = false;
	
	std::unordered_map<std::string, int> data;

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
};


