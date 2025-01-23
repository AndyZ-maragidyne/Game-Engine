#pragma once
#include <variant>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"

class InputHandler : public EventHandler {
public:

	InputHandler(EventManager* eventManager, std::vector<std::unique_ptr<GameObject>>* entityList) : manager(eventManager), entityList(entityList) {}


	void onEvent(Event e);

	void setFrameD(int64_t* frame) {
		frame_delta = frame;
	}

private:
	EventManager* manager;
	int64_t* frame_delta;
	std::vector<std::unique_ptr<GameObject>>* entityList;
	float JumpHeight = 40;
	float YVel = JumpHeight;
	bool jumping = false;
};