#pragma once
#include <vector>
#include "Component.hpp"
#include <SDL.h>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

class EventManager;

using json = nlohmann::json;

class GameObject {
public:

	EventManager* manager;

	void setManager(EventManager* m) {
		manager = m;
	}

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

	// User values + collision constructor
	GameObject(int x, int y, int w, int h, std::string cId, bool collision)
		: xPosition(x), yPosition(y), width(w), height(h), controlId(cId), dead(false), collision(collision) {}

	// User values + collition + isPlayer constructor
	GameObject(int x, int y, int w, int h, std::string cId, bool collision, bool isPlayer)
		: xPosition(x), yPosition(y), width(w), height(h), controlId(cId), dead(false), collision(collision), isPlayer(isPlayer) {}

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

	void setSpawn(bool a) {
		isSpawn = a;
	}

	bool getSpawn() {
		return isSpawn;
	}

	void setPlayer(bool a) {
		isPlayer = a;
	}

	void setxPosition(float x) {
		xPosition = x;
	}

	void setyPosition(float y) {
		yPosition = y;
	}

	bool getPlayer() {
		return isPlayer;
	}

	std::string getID() {
		return controlId;
	}

	void destroy() {
		collision = false;
		isPlayer = false;
		components.clear();
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


private:
	float xPosition;
	float yPosition;
	int width;
	int height;
	std::string controlId;
	std::vector<Component*> components;
	bool dead;
	bool collision = false;
	bool isSpawn = false;
	bool isPlayer = false;
};