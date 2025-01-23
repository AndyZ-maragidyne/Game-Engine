#pragma once
#include "Component.hpp"
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

class SpawnpointComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;
	std::vector<std::unique_ptr<GameObject>>* invisible;
	GameObject* spawn;
	GameObject* scroller;
	GameObject* otherScroller;

	SpawnpointComponent(GameObject* parent, GameObject* spawn, GameObject* scroller, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, int x, int y);

	virtual void update() override;

	virtual json toJson() override;

	int xPosition;
	int yPosition;
};