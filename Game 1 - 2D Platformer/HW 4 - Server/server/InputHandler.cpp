#pragma once
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "server.hpp"
#include "game.hpp"

void InputHandler::onEvent(Event e) {
	if (e.getType() == EventType::INPUT_EVENT) {
		
        std::string inputs = std::get<std::string>(e.parameters["input"]);
        std::string id = std::get<std::string>(e.parameters["id"]);
        GameObject* player = std::get<GameObject*>(e.parameters["player"]);

        //for each letter in the string, do its corresponding input. 
        for (int i = 0; i < inputs.size(); i++) {


            if (inputs[i] == 'W') {
                jumping = true;
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