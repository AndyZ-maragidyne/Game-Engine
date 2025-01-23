#pragma once
#include "Component.hpp"
#include <cstdint>
#include <vector>
#include <memory>

class PhysicsComponent : public Component {
public:
	int64_t* frame_delta;
	std::vector<std::unique_ptr<GameObject>>* entityList;

	PhysicsComponent(GameObject* parent, float gravity, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta);

	virtual void update() override;
	
	void setGravity(float grav) { gravity = grav; }

	virtual json toJson() override;

private:
	float gravity = 10; //posititve since increasing the value of a y coord moves it down, decreasing moves up
};