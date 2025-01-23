#pragma once
#include "Event.hpp"

class EventHandler {
public:
	virtual void onEvent(Event e) = 0;
};
