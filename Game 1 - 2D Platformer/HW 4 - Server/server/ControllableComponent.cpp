#include "ControllableComponent.hpp"
#include "GameObject.hpp"
#include "server.hpp"


ControllableComponent::ControllableComponent(GameObject* parent, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, EventManager* manager)
    : Component(parent), entityList(entityList), frame_delta(frame_delta), manager(manager) {}




void ControllableComponent::update() {
    //have a pointer to the map, get the input for the client, do its input
    auto it = latestClientMovement.find(parent->getControlId());

    if (it == latestClientMovement.end()) {
        return;
    }

    Event* e = it->second;
    e->parameters["player"] = parent;
    manager->raise(*e);

    //for each letter in the string, do its corresponding input. 
    /*for (int i = 0; i < inputs.size(); i++) {


        if (inputs[i] == 'W') {
            jumping = true;
        }
        else if (inputs[i] == 'A') {
            parent->move(-10, 0, entityList, *frame_delta);
        }
        else if (inputs[i] == 'S') {
            parent->move(0, 10, entityList, *frame_delta);
        }
        else if (inputs[i] == 'D') {
            parent->move(10, 0, entityList, *frame_delta);
        }





    }

    if (jumping) {
        parent->move(0, -YVel, entityList, *frame_delta);
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
    }*/

}

json ControllableComponent::toJson() {
    return {
        {"type", "Controllable"}
    };
}