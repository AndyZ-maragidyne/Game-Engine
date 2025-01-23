#include "AIComponent.hpp"
#include "GameObject.hpp"

AIComponent::AIComponent(GameObject* parent, int xPattern, int yPattern, int ticRepeat, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta)
    : Component(parent), xMove(xPattern), yMove(yPattern), repeat(ticRepeat), entityList(entityList), frame_delta(frame_delta) {}

void AIComponent::update() {

	if (turn < (repeat / 2)) {
		parent->move(xMove, yMove, entityList, *frame_delta);
		turn++;
	}
	else if (turn >= (repeat / 2) && turn <= repeat) {
		parent->move(( - 1 * xMove), (-1 * yMove), entityList, *frame_delta);
		turn++;
		if (turn >= repeat) {
			turn = 0;
		}
	}
}

json AIComponent::toJson() {
	return {
		{"type", "AIComponent"},
		{"xMove", xMove},
		{"yMove", yMove},
		{"repeat", repeat},
		{"turn", turn}
	};
}