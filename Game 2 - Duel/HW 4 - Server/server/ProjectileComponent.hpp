#pragma once
#include "Component.hpp"
#include "EventManager.hpp"
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

class ProjectileComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;
	std::vector<std::unique_ptr<GameObject>>* invisibleEntityList;
	EventManager* manager;
	float xMove;
	float yMove;
	int64_t* frame_delta;


	ProjectileComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisibleEntityList, EventManager* manager, float xMove, float yMove, int64_t* frame_delta);

	virtual void update() override;

	virtual json toJson() override;
};