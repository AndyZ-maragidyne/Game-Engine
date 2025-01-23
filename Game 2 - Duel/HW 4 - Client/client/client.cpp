#include "client.hpp"
#include <iostream>


int64_t frame_delta = 0;

void sendToServer(zmq::socket_t& client, Event e) {
    //runs the getClientInput method from input.cpp. It returns a string with which keys are pressed down (WASD)
    std::string playerInput = std::get<std::string>(e.parameters["input"]);
    std::string processId = std::get<std::string>(e.parameters["id"]);
    std::string requestString = processId + "\n" + playerInput;

    //send over the string to the server
    zmq::message_t request(requestString.size());
    memcpy(request.data(), requestString.c_str(), requestString.size());
    client.send(request, zmq::send_flags::none);
}

std::vector<std::unique_ptr<GameObject>> recieveFromServer(zmq::socket_t& client) {
    //gets the reply from the server
    zmq::message_t reply;
    client.recv(reply, zmq::recv_flags::none);

    //uses the information from the json data to create the entities
    std::string entityJsonString(static_cast<char*>(reply.data()), reply.size());

    std::vector<std::unique_ptr<GameObject>> entityList;

    auto entityListPtr = &entityList;

    size_t start = 0;
    size_t end = 0;

    json entityJson = json::parse(entityJsonString);

    for (const auto& e : entityJson) {
        GameObject o = GameObject::fromJson(e, entityListPtr, &frame_delta);
        entityList.push_back(std::make_unique<GameObject>(std::move(o)));
    }


    return entityList;
}