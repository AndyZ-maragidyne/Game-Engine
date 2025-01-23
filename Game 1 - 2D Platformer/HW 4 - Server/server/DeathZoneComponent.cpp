#include "DeathZoneComponent.hpp"
#include "GameObject.hpp"

DeathZoneComponent::DeathZoneComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisibleEntityList, EventManager * manager)
	: Component(parent), entityList(entityList), invisibleEntityList(invisibleEntityList), manager(manager) {}


void DeathZoneComponent::update()
{
	SDL_Rect entityRect = parent->getRect(); //main entity (moving entity)
	for (auto&& e : *entityList) {
		if (e->getPlayer()) {
			SDL_Rect objRect = e->getRect(); //secondary entity (not moving)
			if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != parent) {
				e->setDeath(true);
				Event d(EventType::DEATH_EVENT);
				d.parameters["player"] = (GameObject *) &e;
				d.parameters["playerxpos"] = e->getxPosition();
				d.parameters["invisibleEntityList"] = invisibleEntityList;
				d.parameters["entityList"] = entityList;
				manager->raise(d);
				//move this to eventHandler
				//----------------------------------------------
				/*e->setDeath(true);
				int closestDistance = -1;
				int closestX = 0;
				int closestY = 0;
				GameObject* g = nullptr;
				for (auto& f : *invisibleEntityList) {
					if (f->getSpawn()) {
						if (f->getxPosition() < e->getxPosition()) {
							if (closestDistance == -1 || closestDistance > (e->getxPosition() - f->getxPosition())) {
								g = f.get();
								closestDistance = e->getxPosition() - f->getxPosition();
								closestY = f->getyPosition();
								closestX = f->getxPosition();
							}
						}
					}
				}
				e->setPosition(closestX, closestY);
				if (g != nullptr) {

					g->run();
				}*/
				//----------------------------------------------------
			}
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