#include "ProjectileComponent.hpp"
#include "GameObject.hpp"

ProjectileComponent::ProjectileComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisibleEntityList, EventManager* manager, float xMove, float yMove, int64_t* frame_delta)
	: Component(parent), entityList(entityList), invisibleEntityList(invisibleEntityList), manager(manager), xMove(xMove), yMove(yMove), frame_delta(frame_delta) {}

void ProjectileComponent::update()
{
	// move function
	// if they collide, and its a player, mark the player as dead
	parent->move(xMove, yMove, entityList, *frame_delta);
	SDL_Rect entityRect = parent->getRect();
	for (auto&& e : *entityList) {
		if (e->getPlayer()) {
			SDL_Rect objRect = e->getRect(); //secondary entity (not moving)
			if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != parent) {
				e->setDeath(true);
				e->setxPosition(-10000);
				e->setyPosition(-10000);

				
			}
		}
		else {
			SDL_Rect objRect = e->getRect();
			if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != parent) {

				parent->setDraw(false);
				parent->setxPosition(-10000);
				parent->setyPosition(-10000);
				this->xMove = 0;
				this->yMove = 0;
			}
		}
	}

}

json ProjectileComponent::toJson()
{
	return {
		{"type", "Projectile"}
	};
}