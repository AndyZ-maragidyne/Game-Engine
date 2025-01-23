#include "ControllableComponent.hpp"
#include "GameObject.hpp"


ControllableComponent::ControllableComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta)
    : Component(parent), entityList(entityList), frame_delta(frame_delta) {}


void ControllableComponent::update() {

    
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if (keyboard[SDL_SCANCODE_W])
        {
           
                   parent->move(0, -20, entityList, *frame_delta);
           
           
        }
        if (keyboard[SDL_SCANCODE_A])
        {
           
                    parent->move(-10, 0, entityList, *frame_delta);
                
        }
        if (keyboard[SDL_SCANCODE_S])
        {
            
                    parent->move(0, 10, entityList, *frame_delta);
                
        }
        if (keyboard[SDL_SCANCODE_D])
        {
            
                    parent->move(10, 0, entityList, *frame_delta);
                
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

json ControllableComponent::toJson() {
    return {
        {"type", "Controllable"}
    };
}