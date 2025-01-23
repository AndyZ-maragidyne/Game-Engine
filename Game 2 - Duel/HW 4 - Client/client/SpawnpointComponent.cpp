#include "SpawnpointComponent.hpp"
#include "GameObject.hpp"

SpawnpointComponent::SpawnpointComponent(GameObject* parent, GameObject* spawn, GameObject* scroller, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, int x, int y)
	: Component(parent), spawn(spawn), scroller(scroller), otherScroller(otherScroller), entityList(entityList), invisible(invisible), xPosition(x), yPosition(y) {}

void SpawnpointComponent::update()
{
	int xdistance = spawn->getxPosition() - xPosition; //current - starting position = distance moved from spawnpoint horizontally
	int ydistance = yPosition - spawn->getyPosition(); //start - current position = distance moved from spawnpoint vertically
	if (parent->isDead()) {
		for (auto&& e : *entityList) {
			e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
		}
		for (auto&& e : *invisible) {
			if (e.get() != scroller && e.get() != otherScroller) {
				e->setPosition(e->getxPosition() - xdistance, e->getyPosition() + ydistance);
			}
		}
		parent->setPosition(xPosition, yPosition);
		parent->setDeath(false);
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