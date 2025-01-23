#pragma once
#include <map>
#include <variant>
#include <string>
#include "GameObject.hpp"

using Variant = std::variant<int, float, int64_t, std::string, GameObject*, std::vector<std::unique_ptr<GameObject>>* >;

enum class EventType {
    COLLISION_EVENT,
    DEATH_EVENT,
    SPAWN_EVENT,
    INPUT_EVENT
};

class Event {
public:
    Event(EventType type) : type(type), timestamp(NULL) {}

    EventType getType() const {
        return type;
    }

    void setTimeStamp(int64_t t) {
        timestamp = t;
    }

    int64_t getTimeStamp() {
        return timestamp;
    }

    std::map<std::string, Variant> parameters;

private:
    EventType type;
    int64_t timestamp;
};
