#pragma once
#include "Component.hpp"
#include <SDL.h>
#include <vector>
#include <memory>

class GameObject;

class ControllableComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;
	int64_t* frame_delta;

	ControllableComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta);

	virtual void update() override;

	virtual json toJson() override;

};