#pragma once
#include "Event.hpp"
#include <nlohmann/json.hpp>


class InputEvent : public Event {
public:

    InputEvent(EventType type, std::string input, std::string id, GameObject* player)
        : Event(type), input(input), id(id), player(player) {}

    std::string input;
    std::string id;
    GameObject* player;

    json toJson() {
        return {
            {"input", input},
            {"id", id}
        };
    }

    static InputEvent fromJson(GameObject* player, const json& j) {
        return InputEvent(EventType::INPUT_EVENT, j.at("input").get<std::string>(), j.at("id").get<std::string>(), player);
    }
};