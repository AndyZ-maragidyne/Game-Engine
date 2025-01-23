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
                if (isPlayer) {
                    (*entityList)[0]->setPosition(1000, 0);
                    (*entityList)[1]->setPosition(1000, 500);
                    (*entityList)[2]->setPosition(2000, 0);
                    (*entityList)[3]->setPosition(2000, 1000);
                    (*entityList)[4]->setPosition(3000, 0);
                    (*entityList)[5]->setPosition(3000, 700);
                    (*entityList)[6]->setPosition(4000, 0);
                    (*entityList)[7]->setPosition(4000, 800);
                    (*entityList)[8]->setPosition(5000, 0);
                    (*entityList)[9]->setPosition(5000, 400);
                    (*entityList)[10]->setPosition(6000, 0);
                    (*entityList)[11]->setPosition(6000, 600);
                    (*entityList)[12]->setPosition(6000, 1000);
                    (*entityList)[13]->setPosition(7000, 0);
                    (*entityList)[14]->setPosition(7000, 1000);
                    (*entityList)[15]->setPosition(8000, 0);
                    (*entityList)[16]->setPosition(8000, 600);
                    (*entityList)[17]->setPosition(9000, 0);
                    (*entityList)[18]->setPosition(9000, 750);
                    (*entityList)[19]->setPosition(10000, 0);
                    (*entityList)[20]->setPosition(10000, 525);
                    (*entityList)[21]->setPosition(500, 200);
                    return false;
                }
                //// Create a collision event, passing the current GameObject and the other object
                //Event* c = new Event(EventType::COLLISION_EVENT);
                //c->parameters["player"] = this;  // Pass the current GameObject instance
                //c->parameters["entity"] = e.get();  // Pass the other GameObject instance
                //c->parameters["entityList"] = entityList;
                //c->parameters["x"] = x;
                //c->parameters["y"] = y;
                //c->parameters["elapsedTicks"] = elapsedTicks;

                //manager->raise(*c);
                if ((yPosition <= (e->getyPosition() + e->getHeight())) //collision between top or bottom, do the opposite
                    || (yPosition + height) >= e->getyPosition()) {
                    yPosition -= (y * elapsedTicks);
                }
                if (xPosition <= (e->getxPosition() + e->getWidth()) //collision between left or right, do the opposite
                    || (xPosition + width) >= e->getxPosition()) {
                    xPosition -= (x * elapsedTicks);
                }
            }
        }
    }

    return true;
}
