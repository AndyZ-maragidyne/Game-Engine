#include "SpawnpointComponent.hpp"
#include "GameObject.hpp"


SpawnpointComponent::SpawnpointComponent(GameObject* parent, GameObject* spawn, GameObject* scroller, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, EventManager* manager, int x, int y)
	: Component(parent), spawn(spawn), scroller(scroller), otherScroller(otherScroller), entityList(entityList), invisible(invisible), manager(manager), xPosition(x), yPosition(y) {}

void SpawnpointComponent::update()
{
	int xdistance = spawn->getxPosition() - xPosition; //current - starting position = distance moved from spawnpoint horizontally
	int ydistance = yPosition - spawn->getyPosition(); //start - current position = distance moved from spawnpoint vertically

	for (auto&& g : *entityList) {

		if (g->getPlayer() && g->isDead()){
			Event* e = new Event(EventType::SPAWN_EVENT);
			e->parameters["player"] = g.get();
			e->parameters["spawn"] = spawn;
			e->parameters["xPosition"] = xPosition;
			e->parameters["yPosition"] = yPosition;
			e->parameters["entityList"] = entityList;
			e->parameters["invisible"] = invisible;
			e->parameters["scroller"] = scroller;
			e->parameters["otherScroller"] = otherScroller;
			e->parameters["xdistance"] = xdistance;
			e->parameters["ydistance"] = ydistance;
			manager->raise(*e);
			
			/*for (auto&& e : *entityList) {
				e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
			}
			for (auto&& e : *invisible) {
				if (e.get() != scroller && e.get() != otherScroller) {
					e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
				}
			}
			g->setPosition(xPosition, yPosition);
			g->setDeath(false);*/
		}
	}
	return;
}

json SpawnpointComponent::toJson() {
	return {
		{"type", "Spawnpoint"},
		{"xPosition", xPosition},
		{"yPosition", yPosition}
	};
}