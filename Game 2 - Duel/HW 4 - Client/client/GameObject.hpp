#pragma once
#include <vector>
#include "Component.hpp"
#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "AIComponent.hpp"
#include "ControllableComponent.hpp"
#include "DeathZoneComponent.hpp"
#include "DrawComponent.hpp"
#include "PhysicsComponent.hpp"
#include "SidescrollComponent.hpp"
#include "SpawnpointComponent.hpp"
#include "AIComponent.hpp"

class AIComponent;

using json = nlohmann::json;

class GameObject {
public:
	void addComponent(Component* comp) {
		components.push_back(comp);

	}

	void run() {
		for (auto& c : components) {
			c->update();
		}
	}


	// Default constructor
	GameObject() : xPosition(0), yPosition(0), width(10), height(10), dead(false) {}

	// User values constructor
	GameObject(int x, int y, int w, int h, std::string cId)
		: xPosition(x), yPosition(y), width(w), height(h), controlId(cId), dead(false) {}

	// No client ID constructor
	GameObject(int x, int y, int w, int h)
		: xPosition(x), yPosition(y), width(w), height(h), controlId("NULL"), dead(false) {}

	bool move(float x, float y, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t elapsedTicks);
	float getxPosition() { return xPosition; }
	float getyPosition() { return yPosition; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	std::string getControlId() { return controlId; }

	SDL_Rect getRect() const {
		SDL_Rect rec = { (int)xPosition , (int)yPosition, (int)width, (int)height };
		return rec;
	}


	std::string toString() {
		std::string sendStr = std::to_string(xPosition);
		sendStr += "\n" + std::to_string(yPosition);
		sendStr += "\n" + std::to_string(width);
		sendStr += "\n" + std::to_string(height);
		sendStr += "\n" + controlId;

		return sendStr;
	}

	bool isDead() {
		return dead;
	}

	void setDeath(bool d) {
		dead = d;
	}

	void setCollide(bool c) {
		collision = c;
	}

	void setPosition(int x, int y) {
		xPosition = x;
		yPosition = y;
	}

	json toJson() const {
		json jsonComponents = json::array();

		for (const auto& c : components) {
			jsonComponents.push_back(c->toJson());
		}

		return json{
			{"xPosition", xPosition},
			{"yPosition", yPosition},
			{"width", width},
			{"height", height},
			{"controlId", controlId},
			{"dead", dead},
			{"collision", collision},
			{"components", jsonComponents}
		};
	}

	static GameObject fromJson(const json& j, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta) {
		GameObject* object = new GameObject(j.at("xPosition").get<float>(), j.at("yPosition").get<float>(), j.at("width").get<int>(), j.at("height").get<int>(), j.at("controlId").get<std::string>());
		object->setDeath(j.at("dead").get<bool>());
		object->setCollide(j.at("collision").get<bool>());

		for (const auto& jc : j.at("components")) {
			std::string type = jc.at("type").get<std::string>();

			
			if (type == "Draw") {
				object->addComponent(new DrawComponent(object, jc.at("red").get<Uint8>(), jc.at("green").get<Uint8>(), jc.at("blue").get<Uint8>()));
			}
			
		}

		return *object;
	}

private:
	float xPosition;
	float yPosition;
	int width;
	int height;
	std::string controlId;
	std::vector<Component*> components;
	bool dead;
	bool collision = false;
};