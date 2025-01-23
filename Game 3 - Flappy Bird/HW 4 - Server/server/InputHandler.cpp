#pragma once
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "server.hpp"
#include "game.hpp"
#include "ProjectileComponent.hpp"
#include "DrawComponent.hpp"

void InputHandler::onEvent(Event e) {
	if (e.getType() == EventType::INPUT_EVENT) {
        JumpHeight = 23;
        std::string inputs = std::get<std::string>(e.parameters["input"]);
        std::string id = std::get<std::string>(e.parameters["id"]);
        GameObject* player = std::get<GameObject*>(e.parameters["player"]);

        //for each letter in the string, do its corresponding input. 
        for (int i = 0; i < inputs.size(); i++) {

            if (player->getPlayerNum() == 1) {
                if (inputs[i] == 'W') {
                    if (!jumping) {
                        jumping = true;
                    }
                }
   
            }



        }

        if (jumping && player) {
            player->move(0, -YVel, entityList, *frame_delta);
            YVel -= 5;
            if (YVel < -15) {
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