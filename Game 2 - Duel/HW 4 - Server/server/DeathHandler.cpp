#pragma once
#include "DeathHandler.hpp"
#include "SpawnEvent.hpp"

void DeathHandler::onEvent(Event e) {
	if (e.getType() == EventType::DEATH_EVENT) {
		GameObject* player = std::get<GameObject*>(e.parameters["player"]);
		std::vector<std::unique_ptr<GameObject>>* invisibleEntityList = std::get<std::vector<std::unique_ptr<GameObject>>*>(e.parameters["invisibleEntityList"]);
		float playerxpos = std::get<float>(e.parameters["playerxpos"]);

		player->setDeath(true);
		bool found = false;
		int closestDistance = -1;
		int closestX = 0;
		int closestY = 0;
		GameObject* g = nullptr;
		for (auto& f : *invisibleEntityList) {
			if (f->getSpawn()) {
				if (!found) {
					found = true;
					g = f.get();
					closestDistance = playerxpos - f->getxPosition();
					closestY = f->getyPosition();
					closestX = f->getxPosition();
				}
				else {
					if (f->getxPosition() < playerxpos) {
						if (closestDistance == -1 || closestDistance > (playerxpos - f->getxPosition())) {
							g = f.get();
							closestDistance = playerxpos - f->getxPosition();
							closestY = f->getyPosition();
							closestX = f->getxPosition();
						}
					}
				}
			}
		}
		//player->setPosition(closestX, closestY);
		if (g != nullptr) {
			g->run();
		}
	}

}