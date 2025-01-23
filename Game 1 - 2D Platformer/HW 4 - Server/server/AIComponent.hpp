#pragma once
#include "Component.hpp"
#include "GameObject.hpp"

class AIComponent : public Component {
public:
	AIComponent(GameObject* parent, int xPattern, int yPattern, int ticRepeat, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta);

	virtual void update() override;

	virtual json toJson() override;

private:
	int xMove;
	int yMove;
	int repeat;
	int turn = 0;
	std::vector<std::unique_ptr<GameObject>>* entityList;
	int64_t* frame_delta;
};