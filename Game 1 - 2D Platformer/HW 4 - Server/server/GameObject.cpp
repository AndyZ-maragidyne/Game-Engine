#pragma once
#include <variant>
#include <iostream>
#include "GameObject.hpp"
#include "Event.hpp"
#include "EventManager.hpp"

//Allows the entity to move.
bool GameObject::move(float x, float y, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t elapsedTicks)
{
    // Calculate movement deltas based on elapsed ticks
    float deltaX = x * elapsedTicks;
    float deltaY = y * elapsedTicks;

    // Update the current position
    xPosition += deltaX;
    yPosition += deltaY;

    if (collision) {
        SDL_Rect entityRect = getRect();  // Current entity's rectangle
        for (auto&& e : *entityList) {
            SDL_Rect objRect = e->getRect(); // Other entity's rectangle
            if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != this) {

                // Create a collision event, passing the current GameObject and the other object
                Event* c = new Event(EventType::COLLISION_EVENT);
                c->parameters["player"] = this;  // Pass the current GameObject instance
                c->parameters["entity"] = e.get();  // Pass the other GameObject instance
                c->parameters["entityList"] = entityList;
                c->parameters["x"] = x;
                c->parameters["y"] = y;
                c->parameters["elapsedTicks"] = elapsedTicks;

                manager->raise(*c);
                //if ((yPosition <= (e->getyPosition() + e->getHeight())) //collision between top or bottom, do the opposite
                //    || (yPosition + height) >= e->getyPosition()) {
                //    yPosition -= (y * elapsedTicks);
                //}
                //if (xPosition <= (e->getxPosition() + e->getWidth()) //collision between left or right, do the opposite
                //    || (xPosition + width) >= e->getxPosition()) {
                //    xPosition -= (x * elapsedTicks);
                //}
            }
        }
    }

    return true;
}
