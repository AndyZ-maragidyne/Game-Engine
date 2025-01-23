#include "input.hpp"

/*
* This function is boilerplate, and the contents currently read the events thrown by SDL and look for the SDL quit event, terminating the program.
* This file is where code to read the keyboard state and determine which keys are pressed should sit.
*/

bool slow = false;
bool base = true;
bool fast = false;

void doInput(std::vector<std::unique_ptr<Entity>>* entityList, int64_t frame_delta)
{

    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    if (keyboard[SDL_SCANCODE_W])
    {
        for (auto&& e : *entityList) {
            if(e->getControllable()){
                e->move(0, -20, entityList, &e, frame_delta);
            }
        }
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        for (auto&& e : *entityList) {
            if (e->getControllable()) {
                e->move(-10, 0, entityList, &e, frame_delta);
            }
        }
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        for (auto&& e : *entityList) {
            if (e->getControllable()) {
                e->move(0, 10, entityList, &e, frame_delta);
            }
        }
    }
    if (keyboard[SDL_SCANCODE_D])
    {
        for (auto&& e : *entityList) {
            if (e->getControllable()) {
                e->move(10, 0, entityList, &e, frame_delta);
            }
        }
    }
    if (keyboard[SDL_SCANCODE_1])
    {
        SDL_SetWindowSize(app->window, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    if (keyboard[SDL_SCANCODE_2])
    {
        SDL_SetWindowSize(app->window, 1280, 720);
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


void doClientInput(std::vector<std::unique_ptr<Entity>>* entityList, int64_t frame_delta, std::string clientID, std::string inputs, Timeline *t)
{
    //for each letter in the string, do its corresponding input. 
    for (int i = 0; i < inputs.size(); i++) {
        for (auto&& e : *entityList) {
            if (e->getControllable() && (e->getControlId() == clientID)) {
                if (inputs[i] == 'W' && !(t->isPaused())) { 
                   e->move(0, -20, entityList, &e, frame_delta);                                     
                }
                else if (inputs[i] == 'A' && !(t->isPaused())) {
                    e->move(-10, 0, entityList, &e, frame_delta);                                            
                }
                else if (inputs[i] == 'S' && !(t->isPaused())) {
                    e->move(0, 10, entityList, &e, frame_delta);                                          
                }
                else if (inputs[i] == 'D' && !(t->isPaused())) {
                    e->move(10, 0, entityList, &e, frame_delta);                                           
                }
                else if (inputs[i] == 'O') {
                    if (t->isPaused()) {
                        t->unpause();
                    }
                }
                else if (inputs[i] == 'P') {
                    if (!(t->isPaused())) {
                        t->pause();
                    }
                }
                else if (inputs[i] == 'J') { //half speed
                    if (base) {
                        base = false;
                        slow = true;
                        fast = false;
                        t->changeTic((t->getTic() * 2));
                    }
                    else if (fast) {
                        base = false;
                        slow = true;
                        fast = false;
                        t->changeTic((t->getTic() * 4));
                    }
                }
                else if (inputs[i] == 'K') { //base speed
                    if (slow) {
                        base = true;
                        slow = false;
                        fast = false;
                        t->changeTic((t->getTic() / 2));
                    }
                    else if (fast) {
                        base = true;
                        slow = false;
                        fast = false;
                        t->changeTic((t->getTic() * 2));
                    }
                }
                else if (inputs[i] == 'L') {
                    if (base) {
                        base = false;
                        slow = false;
                        fast = true;
                        t->changeTic((t->getTic() / 2));
                    }
                    else if (slow) {
                        base = false;
                        slow = false;
                        fast = true;
                        t->changeTic((t->getTic() / 4));
                    }
                }
            }
        }
    }
        
    
}