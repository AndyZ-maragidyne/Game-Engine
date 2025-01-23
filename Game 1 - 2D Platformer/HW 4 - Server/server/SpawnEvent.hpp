#pragma once
#include "Event.hpp"
#include "GameObject.hpp"

class SpawnEvent : public Event {
public:

    SpawnEvent(EventType type, GameObject* spawn, GameObject* scroller, GameObject* otherScroller, std::vector<std::unique_ptr<GameObject>>* entityList, std::vector<std::unique_ptr<GameObject>>* invisible, int x, int y) 
        :Event(type), spawn(spawn), scroller(scroller), otherScroller(otherScroller), entityList(entityList), invisible(invisible), x(x), y(y) {}
    
    GameObject* spawn;
    GameObject* scroller;
    GameObject* otherScroller;
    std::vector<std::unique_ptr<GameObject>>* entityList;
    std::vector<std::unique_ptr<GameObject>>* invisible;
    int x;
    int y;
};