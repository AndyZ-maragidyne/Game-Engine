#pragma once
#include "input.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "DrawComponent.hpp"
#include "ControllableComponent.hpp"
#include "DeathZoneComponent.hpp"
#include "SpawnpointComponent.hpp"
#include "Event.hpp"
#include <zmq.hpp>
#include <string>


void sendToServer(zmq::socket_t& client, Event e);

std::vector<std::unique_ptr<GameObject>> recieveFromServer(zmq::socket_t& client);
