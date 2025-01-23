#pragma once
#include "Component.hpp"
#include "structs.hpp"

// SDL render and window context
extern App* app;

class DrawComponent : public Component {
public:
	DrawComponent(GameObject* parent);

	DrawComponent(GameObject* parent, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	DrawComponent(GameObject* parent, Uint8 r, Uint8 g, Uint8 b);

	virtual void update() override;

	virtual json toJson() override;

	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;

};