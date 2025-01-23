#pragma once
#include "CollisionHandler.hpp"
#include "GameObject.hpp"
#include "server.hpp"
#include "game.hpp"

void CollisionHandler::onEvent(Event ev) {
    if (ev.getType() == EventType::COLLISION_EVENT) {
        GameObject* player = std::get<GameObject*>(ev.parameters["player"]);
        GameObject* e = std::get<GameObject*>(ev.parameters["entity"]);
        float x = std::get<float>(ev.parameters["x"]);

        float y = std::get<float>(ev.parameters["y"]);
        int64_t elapsedTicks = std::get<int64_t>(ev.parameters["elapsedTicks"]);
        std::vector<std::unique_ptr<GameObject>>* entityList = std::get<std::vector<std::unique_ptr<GameObject>>*>(ev.parameters["entityList"]);


        float playerYPos = player->getyPosition();
        float playerHeight = player->getHeight();
        float playerXPos = player->getxPosition();
        float playerWidth = player->getWidth();


        SDL_Rect entityRect = player->getRect();
        for (auto&& e : *entityList) {
            SDL_Rect objRect = e->getRect(); // Other entity's rectangle
            if (SDL_HasIntersection(&entityRect, &objRect) && e.get() != player) {


                if ((playerYPos <= (e->getyPosition() + e->getHeight())) //collision between top or bottom, do the opposite
                    || (playerYPos + playerHeight) >= e->getyPosition()) {
                    player->setyPosition( playerYPos - (y * elapsedTicks));
                }
                if (playerXPos <= (e->getxPosition() + e->getWidth()) //collision between left or right, do the opposite
                    || (playerXPos + playerWidth) >= e->getxPosition()) {
                    player->setxPosition( playerXPos - (x * elapsedTicks));
                }
            }
        }

    }
}

