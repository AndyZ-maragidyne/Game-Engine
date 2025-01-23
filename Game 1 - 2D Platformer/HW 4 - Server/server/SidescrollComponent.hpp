#pragma once
#include "Component.hpp"
#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

class SidescrollComponent : public Component {
public:
	int64_t* frame_delta;
	std::vector<std::unique_ptr<GameObject>>* entityList;
	std::vector<std::unique_ptr<GameObject>>* invisible;
	GameObject* player;
	GameObject* otherScroller; 

	SidescrollComponent(GameObject* parent, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, int64_t* frame_delta);

	virtual void update() override;

	virtual json toJson() override;

	void setScroll(float scrolling) { scroll = scrolling; }
private:
	float scroll = -10;
};
