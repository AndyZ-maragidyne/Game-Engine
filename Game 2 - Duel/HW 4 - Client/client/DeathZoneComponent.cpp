#include "DeathZoneComponent.hpp"
#include "GameObject.hpp"

DeathZoneComponent::DeathZoneComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList)
	: Component(parent), entityList(entityList) {}


void DeathZoneComponent::update()
{
	SDL_Rect entityRect = parent->getRect(); //main entity (moving entity)
	for (auto&& e : *entityList) {
		SDL_Rect objRect = e->getRect(); //secondary entity (not moving)
		if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != parent) {
			e->setDeath(true);
		}
	}
	return;
}

json DeathZoneComponent::toJson()
{
	return {
		{"type", "DeathZone"}
	};
}