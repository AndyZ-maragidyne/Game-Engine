#pragma once
#include "Event.hpp"

class InputEvent : public Event {
public:

    InputEvent(EventType type, std::string input, std::string id, GameObject* player)
        : Event(type), input(input), id(id), player(player) {}

    std::string input;
    std::string id;
    GameObject* player;
};