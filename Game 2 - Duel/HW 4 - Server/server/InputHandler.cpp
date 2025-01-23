#pragma once
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "server.hpp"
#include "game.hpp"
#include "ProjectileComponent.hpp"
#include "DrawComponent.hpp"

void InputHandler::onEvent(Event e) {
	if (e.getType() == EventType::INPUT_EVENT) {
		
        std::string inputs = std::get<std::string>(e.parameters["input"]);
        std::string id = std::get<std::string>(e.parameters["id"]);
        GameObject* player = std::get<GameObject*>(e.parameters["player"]);

        //for each letter in the string, do its corresponding input. 
        for (int i = 0; i < inputs.size(); i++) {

            if (player->getPlayerNum() == 1) {
                if (inputs[i] == 'W') {
                    player->move(0, -10, entityList, *frame_delta);
                }
                else if (inputs[i] == 'A') {
                    player->move(-10, 0, entityList, *frame_delta);
                }
                else if (inputs[i] == 'S') {
                    player->move(0, 10, entityList, *frame_delta);
                }
                else if (inputs[i] == 'D') {
                    player->move(10, 0, entityList, *frame_delta);
                }
                else if (inputs[i] == 'V') {
                    if (lastShootTime1 < t->getTime() - 500) {
                        lastShootTime1 = t->getTime();
                        //spawn projectile, 25 by 25, right in front of player (top)
                        auto projectile = std::make_unique<GameObject>(player->getxPosition() + 12, player->getyPosition() - player->getHeight() + 50, 25, 25);
                        projectile->addComponent(new ProjectileComponent(projectile.get(), getList(), getInvisibleList(), getManager(), 0, -10, frame_delta));
                        projectile->addComponent(new DrawComponent(projectile.get()));
                        entityList->push_back(std::move(projectile));
                    }
                }
            }


            if (player->getPlayerNum() == 2) {
                if (inputs[i] == 'I') {
                    player->move(0, -10, entityList, *frame_delta);
                }
                else if (inputs[i] == 'J') {
                    player->move(-10, 0, entityList, *frame_delta);
                }
                else if (inputs[i] == 'K') {
                    player->move(0, 10, entityList, *frame_delta);
                }
                else if (inputs[i] == 'L') {
                    player->move(10, 0, entityList, *frame_delta);
                }
                else if (inputs[i] == '/') {
                    if (lastShootTime2 < t->getTime() - 500) {
                        lastShootTime2 = t->getTime();
                        //spawn projectile, 25 by 25, right in front of player (top)
                        auto projectile = std::make_unique<GameObject>(player->getxPosition() + 12, player->getyPosition() + player->getHeight(), 25, 25);
                        projectile->addComponent(new ProjectileComponent(projectile.get(), getList(), getInvisibleList(), getManager(), 0, 10, frame_delta));
                        projectile->addComponent(new DrawComponent(projectile.get()));
                        entityList->push_back(std::move(projectile));
                    }
                }
            }


        }

        if (jumping && player) {
            player->move(0, -YVel, entityList, *frame_delta);
            YVel -= 5;
            if (YVel < -JumpHeight) {
                jumping = false;
                YVel = JumpHeight;
            }
        }


        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
            }
        }
	}

}