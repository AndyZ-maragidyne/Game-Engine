#pragma once
#include <map>
#include <vector>
#include <list>
#include <string>
#include "Timeline.hpp"
#include "Event.hpp"
#include "EventHandler.hpp"


class EventManager {
public:
	EventManager(Timeline * t);
	Timeline* t;
	void registerEvent(std::list<EventType>, EventHandler *);
	void deregister(std::list<EventType>, EventHandler *);
	void raise(Event);
	void handleEvents();
private:
	std::map<EventType, std::list<EventHandler*>> handlers;
	std::vector<Event> raisedEvents;
};