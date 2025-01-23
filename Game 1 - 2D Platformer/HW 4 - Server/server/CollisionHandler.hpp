#pragma once
#include <variant>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"

class CollisionHandler : public EventHandler {
public:

	CollisionHandler(EventManager* eventManager) : manager(eventManager) {}


	void onEvent(Event e);


private:
	EventManager* manager;
};
