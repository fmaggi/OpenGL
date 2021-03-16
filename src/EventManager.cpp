#include "EventManager.h"

EventManager EventManager::s_EventManager;

void EventManager::dispatch(Events t)
{
    s_EventManager.m_events.push_back(t);
}

std::vector<Events>& EventManager::pollEvents()
{
    s_EventManager.KeyPressed();
    return s_EventManager.m_events;
}

void EventManager::handled()
{
    s_EventManager.m_events.clear();
}

void EventManager::KeyPressed()
{
    return;
}


