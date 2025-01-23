#pragma once
#include "Component.hpp"
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

class DeathZoneComponent : public Component {
public:
	std::vector<std::unique_ptr<GameObject>>* entityList;

	DeathZoneComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList);

	virtual void update() override;

	virtual json toJson() override;

};