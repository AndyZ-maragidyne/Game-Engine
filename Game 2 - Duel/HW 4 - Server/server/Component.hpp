#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class GameObject;

class Component {
public:
	GameObject* parent;


	Component(GameObject* parent) : parent(parent){}

	virtual void update() = 0;

	virtual json toJson() = 0;

};