#include "input.hpp"

/*
* This function is boilerplate, and the contents currently read the events thrown by SDL and look for the SDL quit event, terminating the program.
* This file is where code to read the keyboard state and determine which keys are pressed should sit.
*/
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


std::string getClientInput() {
     std::string outputs = "";

    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_W]) {
        outputs += "W";
    }
    if (keyboard[SDL_SCANCODE_A]) {
        outputs += "A";
    }
    if (keyboard[SDL_SCANCODE_S]) {
        outputs += "S";
    }
    if (keyboard[SDL_SCANCODE_D]) {
        outputs += "D";
    }
    if (keyboard[SDL_SCANCODE_O]) {
        outputs += "O";
    }
    if (keyboard[SDL_SCANCODE_P]) {
        outputs += "P";
    }
    if (keyboard[SDL_SCANCODE_J]) {
        outputs += "J";
    }
    if (keyboard[SDL_SCANCODE_K]) {
        outputs += "K";
    }
    if (keyboard[SDL_SCANCODE_L]) {
        outputs += "L";
    }


   

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDLK_w:
            outputs += "W";
            break;
        case SDLK_a:
            outputs += "A"; 
            break;
        case SDLK_s:
            outputs += "S";  
            break;
        case SDLK_d:
            outputs += "D"; 
            break;
        case SDLK_p:
            outputs += "P";  
            break;
        case SDLK_o:
            outputs += "O"; 
            break;
        case SDLK_j:
            outputs += "J"; 
            break;
        case SDLK_k:
            outputs += "K"; 
            break;
        case SDLK_l:
            outputs += "L"; 
            break;
        default:
            break;
        }
    }

    return outputs;
}