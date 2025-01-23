#pragma once
#include <variant>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"

class SpawnHandler : public EventHandler {
public:

	SpawnHandler(EventManager* eventManager) : manager(eventManager) {}


	void onEvent(Event e);

private:
	EventManager* manager;
};

