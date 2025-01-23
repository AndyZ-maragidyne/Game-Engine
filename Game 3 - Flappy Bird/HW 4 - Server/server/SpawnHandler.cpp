#include "SpawnHandler.hpp"

void SpawnHandler::onEvent(Event e)
{
	GameObject* spawn = std::get<GameObject*>(e.parameters["spawn"]);
	GameObject* player = std::get<GameObject*>(e.parameters["player"]);
	int xPosition = std::get<int>(e.parameters["xPosition"]);
	int yPosition = std::get<int>(e.parameters["yPosition"]);
	std::vector<std::unique_ptr<GameObject>>*  entityList = std::get<std::vector<std::unique_ptr<GameObject>>*>(e.parameters["entityList"]);
	std::vector<std::unique_ptr<GameObject>>* invisible = std::get<std::vector<std::unique_ptr<GameObject>>*>(e.parameters["invisible"]);
	GameObject* scroller = std::get<GameObject*>(e.parameters["scroller"]);
	GameObject* otherScroller = std::get<GameObject*>(e.parameters["otherScroller"]);
	int xdistance = std::get<int>(e.parameters["xdistance"]);
	int ydistance = std::get<int>(e.parameters["ydistance"]);

	int closestDistance = -1;
	int closestX = 0;
	int closestY = 0;
	if (!player->isDead()) {
		return;
	}
	GameObject* g = nullptr;
	for (auto& f : *invisible) {
		if (f->getSpawn()) {
			if (f->getxPosition() < player->getxPosition()) {
				if (closestDistance == -1 || closestDistance > (player->getxPosition() - f->getxPosition())) {
					g = f.get();
					closestDistance = player->getxPosition() - f->getxPosition();
					closestY = f->getyPosition();
					closestX = f->getxPosition();
				}
			}
		}
	}
	player->setPosition(closestX, closestY);
	for (auto&& e : *entityList) {
		e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
	}
	for (auto&& e : *invisible) {
		if (e.get() != scroller && e.get() != otherScroller) {
			e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
		}
	}
	//player->setPosition(xPosition, yPosition);
	player->setDeath(false);
	
}
