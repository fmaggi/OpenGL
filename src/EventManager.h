#pragma once
#include "Core.h"

enum class EventType
{
	None = 0,
	Resize, WinClose,
	KeyPressed,
	Done
};

class Event
{
public:
	Event(EventType t)
		: type(t)
	{};

	inline EventType getType() { return type; }	
	std::unordered_map<std::string, int> data;

private:
	EventType type = EventType::None;
};

class EventManager
{
public:
	EventManager(const EventManager&) = delete;
	static void dispatch(Event t);
	static std::vector<Event>& pollEvents();
	static void handled();
private:
	EventManager() {};

	std::vector<Event> m_events;
	static EventManager s_EventManager;
};


