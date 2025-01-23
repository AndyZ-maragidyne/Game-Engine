#include "GameObject.hpp"

//Allows the entity to move.
bool GameObject::move(float x, float y, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t elapsedTicks)
{
	xPosition += (x * elapsedTicks);
	yPosition += (y * elapsedTicks);

	//collision prototype
	if (collision) {
		SDL_Rect entityRect = getRect(); //main entity (moving entity)g
		for (auto&& e : *entityList) {
			SDL_Rect objRect = e->getRect(); //secondary entity (not moving)
			if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != this) {
				if ((yPosition <= (e->getyPosition() + e->getHeight())) //collision between top or bottom, do the opposite
					|| (yPosition + height) >= e->getyPosition()) {
					yPosition -= (y * elapsedTicks);
				}
				if (xPosition <= (e->getxPosition() + e->getWidth()) //collision between left or right, do the opposite
					|| (xPosition + width) >= e->getxPosition()) {
					xPosition -= (x * elapsedTicks);
				}
			}
		}
	}

	return true;
}