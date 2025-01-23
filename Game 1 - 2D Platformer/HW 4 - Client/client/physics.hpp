#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"


//Controls the physics. Rather simplistically applies gravity to the objects by reducing their y-coordinate.
class physics {
public:
	bool applyGravity(std::vector<std::unique_ptr<Entity>>*, int64_t frame_delta);

	void setGravity(float grav) { gravity = grav; }
	
private:
	float gravity = 10; //posititve since increasing the value of a y coord moves it down, decreasing moves up
};