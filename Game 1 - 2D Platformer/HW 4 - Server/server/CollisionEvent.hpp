#pragma once
#include "Event.hpp"

class CollisionEvent : public Event {
public:

    CollisionEvent(EventType type, float yPosition, float deltaY, float height, float xPosition, float deltaX, float width, GameObject* entity) 
        : Event(type), yPosition(yPosition), deltaY(deltaY), height(height), xPosition(xPosition), deltaX(deltaX), width(width), entity(entity) {}

    float yPosition, deltaY, height, xPosition, deltaX, width; //might be better just to pass in the player entity? 
    GameObject* entity; //not sure if its a pointer 
};