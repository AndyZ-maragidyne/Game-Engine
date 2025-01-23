#pragma once
#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
/* This class represents a base game object called an entity. Any object used in the game world could build off the entity class.
*/

class Entity {
public:

	// Default constructor
	Entity() : xPosition(0), yPosition(0), width(10), height(10),
		physics(false), moveable(false), controllable(false) {}

	// User values constructor
	Entity(int x, int y, int w, int h, bool p, bool m, bool c, std::string cId)
		: xPosition(x), yPosition(y), width(w), height(h), physics(p), moveable(m), controllable(c), controlId(cId) {}

	// No client ID constructor
	Entity(int x, int y, int w, int h, bool p, bool m, bool c)
		: xPosition(x), yPosition(y), width(w), height(h), physics(p), moveable(m), controllable(c), controlId("NULL") {}

	bool move(float x, float y, std::vector<std::unique_ptr<Entity>>*, std::unique_ptr<Entity>*, int64_t elapsedTicks);
	float getxPosition() { return xPosition; }
	float getyPosition() { return yPosition; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getPhysics() { return physics; }
	bool getMoveable() { return moveable; }
	bool getControllable() { return controllable; }
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
		if (physics) {
			sendStr += "\n1";
		}
		else {
			sendStr += "\n0";
		}
		if (moveable) {
			sendStr += "\n1";
		}
		else {
			sendStr += "\n0";
		}
		if (controllable) {
			sendStr += "\n1";
		}
		else {
			sendStr += "\n0";
		}
		sendStr += "\n" + controlId;

		return sendStr;
	}

private:
	float xPosition;
	float yPosition;
	int width;
	int height;
	bool physics;
	bool moveable;
	bool controllable;
	std::string controlId;
};