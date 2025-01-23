#pragma once
#include "Component.hpp"
#include "EventManager.hpp"
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

class DeathZoneComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;

	std::vector<std::unique_ptr<GameObject>>* invisibleEntityList;

	EventManager* manager;

	DeathZoneComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisibleEntityList, EventManager* manager);

	virtual void update() override;

	virtual json toJson() override;

};