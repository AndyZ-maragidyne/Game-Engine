#pragma once
#include <variant>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"

class InputHandler : public EventHandler {
public:

	InputHandler(EventManager* eventManager, std::vector<std::unique_ptr<GameObject>>* entityList) : manager(eventManager), entityList(entityList), t(new Timeline()), lastShootTime1(t->getTime()), lastShootTime2(t->getTime()) {}


	void onEvent(Event e);

	void setFrameD(int64_t* frame) {
		frame_delta = frame;
	}

private:
	Timeline* t;
	int64_t lastShootTime1;
	int64_t lastShootTime2;
	EventManager* manager;
	int64_t* frame_delta;
	std::vector<std::unique_ptr<GameObject>>* entityList;
	float JumpHeight = 20;
	float YVel = JumpHeight;
	bool jumping = false;
};