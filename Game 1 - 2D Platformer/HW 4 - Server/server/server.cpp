#include "server.hpp"


//create a list to keep track of the connected clients
std::unordered_map<std::string, Timeline*> activeClientList;
//create a map to keep track of the last message sent from the client.
std::unordered_map<std::string, Event*> latestClientMovement;
//create a map to keep track of disconnects
std::unordered_map<std::string, int> disMap;
//create a list of GameObjects to be removed
std::vector<std::string> rList;

std::string recieveFromClients(zmq::socket_t& server) {
    //get a message from the client
    zmq::message_t request;
    server.recv(request, zmq::recv_flags::none);

    //messageFromClient is the message that the client sent
    std::string messageFromClient(static_cast<char*>(request.data()), request.size());
    return messageFromClient;
}

void processMessages(std::string messageFromClient, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t frame_delta, Timeline* t, EventManager* m) {
    //client sends their processID and any inputs seperated by a /n
    size_t separator = messageFromClient.find("\n");
    //seperate the message to get the clientID and the inputs
    Event* e = new Event(EventType::INPUT_EVENT);
    std::string clientID = messageFromClient.substr(0, separator);
    e->parameters["id"] = clientID;
    e->parameters["input"] = messageFromClient.substr(separator + 1);

    //attempt to find the clientID from the list
    auto foundIt = activeClientList.find(clientID);

    //if the client ID is not found, add it to the list and create a new entity for it
    if (foundIt == activeClientList.end()) {
        Timeline* time = new Timeline(t, t->getTic());
        activeClientList.insert({ clientID, time });
        disMap.insert({ clientID, 0 });

        //sets the control ID to the client's ID when making the new Entity
        auto newEntity = std::make_unique<GameObject>(500, 200, 50, 100, clientID, true, true);
        newEntity->addComponent(new PhysicsComponent(newEntity.get(), 10, entityList, &frame_delta));
        newEntity->addComponent(new DrawComponent(newEntity.get(), 0x00, 0xff, 0x00));
        newEntity->addComponent(new ControllableComponent(newEntity.get(), entityList, &frame_delta, getManager()));
        newEntity->setManager(m);
        entityList->push_back(std::move(newEntity));
        //add the client's input to the map
        latestClientMovement.insert({ clientID, e });
    }
    else {
        //if it is found, update the client's latest input
        latestClientMovement[clientID] = e;
    }

    //Process the client's input

    for (const auto& c : latestClientMovement) {
        int64_t newDelta = activeClientList[c.first]->getFrameD();
        //doClientInput(entityList, newDelta, c.first, c.second, activeClientList[c.first]);
    }

    for (auto& c : disMap) {
        if (c.first != clientID) {
            disMap[c.first]++;
        }
        else {
            disMap[c.first] = 0;
        }

        if (c.second >= 15) {
            rList.push_back(c.first);
        }
    }

    if (!rList.empty()) {
        std::string remID = rList.back();
        rList.pop_back();

        for (auto& e : *entityList) {
            if (e->getID() == remID) {
                auto del = disMap.find(e->getID());
                disMap.erase(del);

                e->destroy();
                e->setPosition(0, 0);
            }
        }
    }

}

void sendToClients(zmq::socket_t& server, std::vector<std::unique_ptr<GameObject>>* entityList) {
    //create a new json in order to send the entity data to thez client
    json entityListJson = json::array();

    // Converts every entity in the entityList to a string
    for (const auto& entity : *entityList) {
        entityListJson.push_back(entity->toJson());
    }


    //send the string with info about every entity to the client
    zmq::message_t message(entityListJson.dump().size());
    memcpy(message.data(), entityListJson.dump().c_str(), entityListJson.dump().size());
    server.send(message, zmq::send_flags::none);
}