#pragma once
#include <string>
#include <algorithm>
#include <zmq.hpp>
#include <unordered_map>
#include <memory>
#include "entity.hpp"
#include "input.hpp"
#include "Timeline.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "DrawComponent.hpp"
#include "ControllableComponent.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "game.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

//create a list to keep track of the connected clients
extern std::unordered_map<std::string, Timeline*> activeClientList;
//create a map to keep track of the last message sent from the client.
extern std::unordered_map<std::string, Event*> latestClientMovement;

std::string recieveFromClients(zmq::socket_t &server);

void processMessages(std::string messageFromClient, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t frame_delta, Timeline* t, EventManager* m);

void sendToClients(zmq::socket_t& server, std::vector<std::unique_ptr<GameObject>>* entityList);