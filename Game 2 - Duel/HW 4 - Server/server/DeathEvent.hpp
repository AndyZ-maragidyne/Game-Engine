#pragma once
#include "Event.hpp"
#include "GameObject.hpp"

class DeathEvent : public Event {
public:

    DeathEvent(EventType type, GameObject* player, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisibleEntityList) 
        : Event(type), player(player), entityList(entityList), invisibleEntityList(invisibleEntityList) {}

    GameObject* player;
    std::vector<std::unique_ptr<GameObject>>* entityList;
    std::vector<std::unique_ptr<GameObject>>* invisibleEntityList;
};