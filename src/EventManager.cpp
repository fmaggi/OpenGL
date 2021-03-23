#include "EventManager.h"

EventManager EventManager::s_EventManager;

void EventManager::dispatch(Event t)
{
    s_EventManager.m_events.push_back(t);
}

std::vector<Event>& EventManager::pollEvents()
{
    return s_EventManager.m_events;
}

void EventManager::handled()
{
    s_EventManager.m_events.clear();
}


