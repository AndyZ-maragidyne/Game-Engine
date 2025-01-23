#pragma once
#include "Component.hpp"
#include "EventManager.hpp"
#include <SDL.h>
#include <vector>
#include <memory>

class GameObject;

class ControllableComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;
	int64_t* frame_delta;

	ControllableComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, EventManager* manager);

	virtual void update() override;

	virtual json toJson() override;

	float JumpHeight = 40;
	float YVel = JumpHeight;
	bool jumping = false;
	EventManager* manager;
};