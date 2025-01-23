#pragma once
#include <variant>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"

class DeathHandler : public EventHandler {
public:

	DeathHandler(EventManager* eventManager) : manager(eventManager) {}


	void onEvent(Event e);

private:
	EventManager* manager;
};

