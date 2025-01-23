#include "SidescrollComponent.hpp"
#include "GameObject.hpp"

SidescrollComponent::SidescrollComponent(GameObject* parent, GameObject* player, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, int64_t* frame_delta)
	: Component(parent), player(player), otherScroller(otherScroller), entityList(entityList), invisible(invisible), frame_delta(frame_delta) {}


void SidescrollComponent::update()
{
	SDL_Rect entityRect = parent->getRect(); //Sidescroll entity
	SDL_Rect playerRect = player->getRect(); //player entity

	if (SDL_HasIntersection(&entityRect, &playerRect)) {
		for (auto&& e : *entityList) {
			if (e.get() != parent) { //dont think i need this if statement since the scroller is in the invisible list
				e->move(scroll, 0, entityList, *frame_delta);
			}
		}
		for (auto&& e : *invisible) {
			if (e.get() != parent && e.get() != otherScroller) {
				e->move(scroll, 0, invisible, *frame_delta);
			}
		}
	}
	return;
}


json SidescrollComponent::toJson()
{
	return {
		{"type", "Sidescroll"},
		{"scroll", scroll}
	};
}