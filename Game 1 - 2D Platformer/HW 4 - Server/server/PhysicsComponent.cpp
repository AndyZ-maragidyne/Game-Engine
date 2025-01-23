#include "PhysicsComponent.hpp"
#include "GameObject.hpp"


PhysicsComponent::PhysicsComponent(GameObject* parent, float gravity, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta) 
	: Component(parent), entityList(entityList), gravity(gravity), frame_delta(frame_delta) {}


void PhysicsComponent::update()
{
	parent->move(0, gravity, entityList, *frame_delta);
	return;
}

json PhysicsComponent::toJson()
{
	return {
		{"type", "Physics"},
		{"gravity", gravity}
	};
}