#include "physics.hpp"

bool physics::applyGravity(std::vector<std::unique_ptr<Entity>>* entityList, int64_t frame_delta)
{
	for (auto&& e : *entityList) {
		//Move every entity by the gravity value
		if(e->getPhysics()){ e->move(0, gravity, entityList, &e, frame_delta); }
	}
	return false;
}